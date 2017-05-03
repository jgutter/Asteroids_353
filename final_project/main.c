// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"
#include "timers.h"
#include "ps2.h"
#include "launchpad_io.h"
#include "ece353_hw2_fonts.h"
#include "lcd.h"
#include "timers.h"
#include <stdbool.h>
#include <eeprom.h>

#define PERIOD_A TIMER_TAMR_TAMR_PERIOD
#define PERIOD_B TIMER_TBMR_TBMR_PERIOD
//15 miliseconds realized from launchpad clock frequency: 50MHz / 66Hz = 500000; 500000 / 100(prescale) = 7500
#define TEN_MS 							7500
//70 miliseconds realize from launchpad clock frequency: 50MHz / 100(prescale) = 500000; 500000 / 35000 = ~14 Hz
#define THIRTY_MS 					35000

#define PS2_HIGH_THRESHOLD 	3072
#define PS2_LOW_THRESHOLD 	1024

#define TIME_INCREMENT			0.070 //from timerB; game updates every 70ms
#define BACKGROUND_COLOR		LCD_COLOR_BLACK
#define TEXT_COLOR					LCD_COLOR_WHITE 

#define NUM_BYTES      8
#define NUM_BYTES_USERNAME 4
#define NUM_BYTES_HIGHSCORE 4

char group[] = "Group22";
char individual_1[] = "Justin Gutter";
char individual_2[] = "Sadeq Hashemi";

char username[4];
wireless_configure_device(myID, remoteID );

typedef enum 
{
  MAIN_MENU,
  IN_GAME, 
	DISPLAY_HIGH_SCORE,
} MODE_t; 		//top level MODE states

bool sw1_pressed, sw2_pressed, io_down_pressed, g_update;
bool ps2_up, ps2_left, ps2_right, ps2_down;


volatile bool ALERT_ADC_UPDATE; 	//Update PS2 ADC values; triggered by TimerB
volatile bool TIMERB_ALERT; 			//Timer B ISR flag
volatile bool TIMERA_ALERT;				//Timer A ISR flag

Game* main_game;									//main game pointer

int PS2_X;												//PS2 controller X value
int PS2_Y;												//PS2 controller Y value

MODE_t mode;									//mode state enumeration


bool sw1_debounce_fsm(void) 			//debounce SW1 state machine
{
  bool pin_logic_level;
  static int debounce_sw1 = 0;
  pin_logic_level = lp_io_read_pin(SW1_BIT);
  
	if (pin_logic_level)
		debounce_sw1 = 0;
	else
		debounce_sw1++;
	
	if(debounce_sw1 == 4)
		return true;
	else
		return false;
}

bool sw2_debounce_fsm(void) 			//debounce SW2 state machine
{
  bool pin_logic_level;
  static int debounce_sw2 = 0;
  pin_logic_level = lp_io_read_pin(SW2_BIT);
  
	if (pin_logic_level)
		debounce_sw2 = 0;
	else
		debounce_sw2++;
	
	if(debounce_sw2 == 1)
		return true;
	else
		return false;
}
//*****************************************************************************
//*****************************************************************************
/*******************************************************************************
* Function Name: 
********************************************************************************
* Summary:  
*
*
* Return:
*  
*
*******************************************************************************/
void queue_command(void){

		PS2_X = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract X value
		PS2_Y = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract Y value
	if(PS2_X > PS2_HIGH_THRESHOLD){ //queue up ps2 right command
		ps2_right = true;
	}	
	else if(PS2_X < PS2_LOW_THRESHOLD){ //queue up ps2 left command
		ps2_left = true;
	}

	if(PS2_Y > PS2_HIGH_THRESHOLD){ //queue up ps2 up command
		ps2_up = true;
	}
	if (sw1_pressed) {
		io_down_pressed = true;
	}
}

//*****************************************************************************
//*****************************************************************************
void initialize_hardware(void)
{
	lp_io_init(); //initialize Launchpad LED's and Push Buttons
	ps2_initialize(); //initialize GPIO pins connected PS2 Joystick
	lcd_config_gpio(); //initialize GPIO pins connected to LCD display
	ft6x06_init();
	eeprom_init();
	gp_timer_config_16(TIMER0_BASE, PERIOD_A, PERIOD_B, false, true); //Initialize timer0 as 2 16-bit periodic (count-down) timers
	gp_timer_period(TIMER0_BASE, TEN_MS, THIRTY_MS); //configure period for timer A to be 10ms & timer b 30ms
																								//both periodic, count-down, and interrupts enabled
}


//*****************************************************************************
//*****************************************************************************
/*******************************************************************************
* Function Name: TimerA_Handler
********************************************************************************
* Summary: TimerA Interrupt Service Routine; 
*
*
* Return:
*  
*
*******************************************************************************/

void TIMER0A_Handler(void) { //interrupt handler for timerA
	TIMERA_ALERT = true;
	((TIMER0_Type*)TIMER0_BASE)->ICR |= TIMER_ICR_TATOCINT; //clear interrupt
}

void TIMER0B_Handler(void) { //interrupt handler for timerB
	TIMERB_ALERT = true;
	((TIMER0_Type*)TIMER0_BASE)->ICR |= TIMER_ICR_TBTOCINT; //clear interrupt
}

void ADC0SS2_Handler(void) { //Sample sequencer 2 interrupt handler
	ALERT_ADC_UPDATE = true;
	((ADC0_Type *)ADC0_BASE)->ISC |= ADC_ISC_IN2;
}

/********************************HIGHSCORE FUNCTIONS********************************************************/
bool screen_pressed(){
	int x; 
	int y;
 if(ft6x06_read_td_status() > 0) return true; 
	
	return false; 
}
bool touch_back_pressed(){	
	int x; 
	int y;
 if(ft6x06_read_td_status() > 0){
			x =  ft6x06_read_x();
	 
			y =  ft6x06_read_y();
	 
	if( (x>(13-10)*17 && x< (13-1)*17) && (y<(19-19)*16 && y> (19-17)*16)){
	return true;
	}

 }	
	return false;
}
//sets highscore and username as 0
bool reset_EEPROM(){
	uint16_t addr;
	bool i2c_status; 
	uint8_t num = 0;
	for(addr = 0; addr <(NUM_BYTES); addr++){			
				i2c_status = eeprom_byte_write(I2C1_BASE,addr, num);			
				if (i2c_status != I2C_OK) return false; //returns false if EEPROM fails 			 						
	}
return true;
}

void draw_screen_input(){
	//17 characters fit
	int i, x, y; 
	int char_ind= 0; 
	int char_num =0;
	
	bool nxt = false; 
	
	char msg[] = "abcdefghijklmnopqrstuvwxyz";	
	char msg0[] = "NEW HIGHSCORE!";
  char msg1[] = "Enter your  initials:";
	char dummy; 

		
	lcd_print_stringXY(msg1,2,5,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	
	lcd_print_stringXY(msg0,0,0,LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	//lcd_print_stringXY(msg0,0,3,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
		
	while(char_num < 3){
	
		read_PS2();
		//if right joystick pressed, increment char_num and reset char_ind
		//char num will count the number of characters entered
		if(X_HIGH){		
				if( char_num != 4)char_num ++; 
				X_HIGH = false; 
		}
		else if(X_LOW){				
				if(char_num != 0) char_num --; 
				X_LOW = false; 
		}
		
		//increments
		if(Y_HIGH){	
			char_ind++;
			if(char_ind == 26) char_ind = 0; //wrap
			Y_HIGH = false;
		}
		else if(Y_LOW){		
			char_ind--; 
			if(char_ind == -1) char_ind = 25;
			Y_LOW = false;			
		}
		
		
		switch(char_num){
			case 0:
					dummy =msg[char_ind];
					username[0] = dummy;
					lcd_print_stringXY(&dummy, 5, 8, LCD_COLOR_BLACK, LCD_COLOR_WHITE);
				break; 
			case 1:
					dummy =msg[char_ind];
					username[1] = dummy;	
					lcd_print_stringXY(&dummy, 6, 8, LCD_COLOR_BLACK, LCD_COLOR_WHITE);
				break; 
			case 2: 
					dummy =msg[char_ind];
					username[2] = dummy;
					lcd_print_stringXY(&dummy, 7, 8, LCD_COLOR_BLACK, LCD_COLOR_WHITE);
				break; 
			case 3:
					username[3] = '\0';
				break;
			}
		
			for(i = 0; i<1005000; i++){}
			//if(touch_back_pressed())break;}
			//if(touch_back_pressed()) break;
		}
			
}

bool save_data(char* usr, int highscore){
	uint16_t addr; 
	uint8_t highscore_byte; 
	char username_char;
	i2c_status_t i2c_status;
	
	for(addr = 0; addr <(NUM_BYTES); addr++){	
									//writes high_score, send MSB first 
									if(addr <  4){ 		
											highscore_byte = highscore >> (8 *(3 - (addr)));									
											i2c_status = eeprom_byte_write(I2C1_BASE,addr, highscore_byte);
										
											if (i2c_status != I2C_OK) break; //printf("ERROR: on read is %d\n\r", i2c_status);
									}
									//writes username starting with the first character
									else{
										 username_char = username[addr - 4];	//takes the appropriate character from username										
										 i2c_status = eeprom_byte_write(I2C1_BASE,addr, username_char);
										
										 if (i2c_status != I2C_OK) break; //printf("ERROR: on read is %d\n\r", i2c_status);
									}
				}
}
	
void read_data(int* highscore){
	uint16_t addr; 
	uint8_t highscore_byte, username_byte; 

	i2c_status_t i2c_status;
	
	for(addr = 0; addr <NUM_BYTES; addr++){	
									//reads high_score, receives MSB first 
									if(addr <  4){ 					
											i2c_status = eeprom_byte_read(I2C1_BASE,addr, &highscore_byte);						
											if (i2c_status != I2C_OK) break; //printf("ERROR: on read is %d\n\r", i2c_status);
											*highscore = ((*highscore)<<8) | highscore_byte;			
									}
									//writes username starting with the first character
									else{
										//takes the appropriate character from username										
										 i2c_status = eeprom_byte_read(I2C1_BASE,addr, &username_byte);
										 if (i2c_status != I2C_OK) break; //printf("ERROR: on read is %d\n\r", i2c_status); 
											username[addr-4] = username_byte; 
									}
				}
}
/********************************MAIN MENU FUNCTIONS*********************************************************************/

void draw_main_menu(void) { //draw main menu text
	char buffer[40];
	strcpy(buffer, "Welcome to");
	lcd_print_stringXY(buffer, 2, 3, TEXT_COLOR, BACKGROUND_COLOR);
	strcpy(buffer, "Asteroids!");
	lcd_print_stringXY(buffer, 2, 4, TEXT_COLOR, BACKGROUND_COLOR);
	strcpy(buffer, "New Game");
	lcd_print_stringXY(buffer, 2, 10, TEXT_COLOR, BACKGROUND_COLOR);
	strcpy(buffer, "High Score");
	lcd_print_stringXY(buffer, 2, 12, TEXT_COLOR, BACKGROUND_COLOR);
}

int touch_menu_pressed(){	
	int x; 
	int y;
	
 if(ft6x06_read_td_status() > 0){
			x =  ft6x06_read_x();
	 
			y =  ft6x06_read_y();
	 
	if( (x>(13-10)*17 && x< (13-1)*17) && (y<(19-9)*16 && y> (19-11)*16)){
	return 1;
	}
	else if((x>(13-10)*17 && x< (13-1)*17) && (y<(19-11)*16 && y> (19-13)*16)) {	
	return 2;
	}
 }	
	return 0;
}

int menu_pressed(void) { //return 1 if new game pressed; return 2 if high score pressed; return 0 otherwise
	if (sw1_pressed)
		return 1;
	else if (sw2_pressed)
		return 2;
	else
		return 0;
}

/********************************WIRELESS***********************************************/
void send_wireless_data(){
	wireless_com_status_t status;
	int32_t valid = 1; 
	int32_t usr; 
	int32_t highscore; 
	int highscore_2;
	

	read_data(&highscore_2);
	highscore = highscore_2;
	
	
	status = wireless_send_32(true, false, valid);
	status = wireless_send_32(true, false, usr);
	status = wireless_send_32(true, false, highscore);
	
}

void receive_wireless_data(){
	wireless_com_status_t status;
	char usr_print[4];
	char highscore_print; 
	uint32_t valid; 
	uint32_t usr; 
	uint32_t highscore;
	static int8_t state = 0; 
	
	switch(state){
		case 0:	//takes start packet
			status = wireless_get_32(false, &valid);
			if(status == NRF24L01_RX_SUCCESS){
				if(valid == 1) state ++;
			}
			break;
			
		case 1: //takes packet with username
			status = wireless_get_32(false, &usr);
			if(status == NRF24L01_RX_SUCCESS){
				state ++;
			}
			else state = 0; 
			break; 
		
		case 2: //takes packet with highscore
			status = wireless_get_32(false, &highscore);
			if(status == NRF24L01_RX_SUCCESS){
				state ++;
			}
			else state = 0; 
			break;
		
		case 3:  //prints them all
			lcd_clear_screen(LCD_COLOR_BLACK);
			*usr_print = (char)usr;
			sprintf(&highscore_print, "%d", highscore);
		
		lcd_print_stringXY(usr_print, 5, 5, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
		lcd_print_stringXY(&highscore_print, 5, 5, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
			break;
		
		default: 
			state = 0; 
			break; 
		
	}
}

bool new_highscore(Game* myGame){
	int high_score;
	int myscore = myGame->score;
	
	uint16_t addr;
  uint8_t values[4];
  uint8_t read_val;
	bool status = true; 
	i2c_status_t i2c_status;  
	
  //reads  4 bytes from EEPROM, with the first byte being upper byte and last byte being 
	//the last byte. 
  for(addr = 0; addr <(NUM_BYTES_HIGHSCORE); addr++)
  {
      i2c_status = eeprom_byte_read(I2C1_BASE,addr, &read_val);	//reads and stores byte in read_val
			
			if (i2c_status != I2C_OK){
				status = false; 
				break;
				}
			else {
			high_score = (high_score << 8) & 0xFFFFFF00; //shifts by one byte and clear lower byte 			
			high_score = high_score | read_val; }
  }		
		//if read was successful, compare scores with old high score
		//and return true
  if(status)
  {
		if( myscore > high_score ){
			return true; 		
		}
  }
	return false; 
}

int	main(void)
{
	int input;
	int delay;
  initialize_hardware();
	lcd_config_screen(); //reset lcd screen
	lcd_clear_screen(LCD_COLOR_BLACK); //clear LCD screen to black
	
 
	
  // Reach infinite loop
  while(1){
		if (TIMERB_ALERT) {
				g_update = true;
				TIMERB_ALERT = false; //clear flag
		}
		if (TIMERA_ALERT) {
				sw1_pressed = sw1_debounce_fsm(); //check if debounced sw1 has been pressed
				sw2_pressed = sw2_debounce_fsm(); //check if debounced sw2 has been pressed
				TIMERA_ALERT = false; //clear flag
		}
		if (ALERT_ADC_UPDATE) {
			PS2_X = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract X value
			PS2_Y = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract Y value
			ALERT_ADC_UPDATE = false;
		}

	input = menu_pressed();
	switch (mode) {
		case MAIN_MENU:{ //main menu loop
			draw_main_menu();	//prints the main menu
			switch (input) {
				case 1:
					mode = IN_GAME;
					main_game = new_game();
					lcd_clear_screen(LCD_COLOR_BLACK);
					break;
				case 2:
					mode = DISPLAY_HIGH_SCORE;
					lcd_clear_screen(LCD_COLOR_BLACK);
					break;
				default:
					mode = MAIN_MENU;
			}
		}
		break;
		case IN_GAME: //in game loop
			if (main_game->status == LOSE || main_game->status == WIN){	

				
					if(new_highscore(main_game)) 		
							mode = DISPLAY_HIGH_SCORE;
				
						else mode = MAIN_MENU;		
			}
			else {
					if (main_game->status == PLAYING) {
						if (sw2_pressed) //pause game if sw2 is pressed
							pause_game(main_game);
							queue_command();
					if (g_update) { //update game on timer B interrupt
						if (ps2_right) {
							rotate_ship_right(&main_game->ship); 	//rotate ship right on PS2 signal
							ps2_right = false;
						}
						if (ps2_left) {													//rotate ship left on PS2 signal
							rotate_ship_left(&main_game->ship);
							ps2_left = false;
						}
						if (ps2_up) {
							accelerate_ship(&main_game->ship);	//accelerate ship on PS2 signal
							ps2_up = false;
						}
						if (io_down_pressed) {
							fire_bullet(main_game->bullets,&main_game->ship);
							io_down_pressed = false;
						}
						update_game(main_game, TIME_INCREMENT); //update game
						g_update = false;
					}
				} else if (main_game->status == PAUSE) { //unpaused 
					if (sw2_pressed)
						resume_game(main_game);
				}
				draw_game(main_game);
			}
		break;
		case DISPLAY_HIGH_SCORE:
			
		
			for (delay =0; delay < 700000; delay++) {}; //delay
			switch (input) {
				case 1:
					mode = MAIN_MENU;
					break;
				case 2:
					mode = MAIN_MENU;
					break;
				default:
					mode = DISPLAY_HIGH_SCORE;
			}
		break;
			
			
		default:
			mode = MAIN_MENU;
	}
		
  };
}
