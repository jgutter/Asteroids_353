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

#define PERIOD_A TIMER_TAMR_TAMR_PERIOD
#define PERIOD_B TIMER_TBMR_TBMR_PERIOD
//10 miliseconds realized from launchpad clock frequency: 50MHz / 100Hz = 500000; 500000 / 100(prescale) = 5000
#define TEN_MS 							5000
//30 miliseconds realize from launchpad clock frequency: 50MHz / 33.3Hz = 1500000; 1500000 / 100(prescale) = 15000
#define THIRTY_MS 					15000

#define PS2_HIGH_THRESHOLD 	3072
#define PS2_LOW_THRESHOLD 	1024

#define BACKGROUND_COLOR		LCD_COLOR_BLACK
#define TEXT_COLOR					LCD_COLOR_WHITE
//CHECK
float curr_time; 

char group[] = "Group22";
char individual_1[] = "Justin Gutter";
char individual_2[] = "Sadeq Hashemi";

typedef enum 
{
  MAIN_MENU,
  IN_GAME, 
	DISPLAY_HIGH_SCORE,
} MODE_t; 		//MODE states

bool sw1_pressed, sw1_pressed, io_down_pressed;
bool ps2_accerlate, ps2_rotate_left, ps2_rotate_right;
volatile bool ALERT_ADC_UPDATE; 	//Update PS2 ADC values; triggered by TimerB
volatile bool TIMERB_ALERT; 			//Timer B ISR flag
volatile bool TIMERA_ALERT;				//Timer A ISR flag
Game* main_game;

static int count_B = 0; 					//private variable to count number of  Timer B interrupts
static int count_A = 0; 					//private variable to count number of Timer A interrupts

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
	
	if(debounce_sw1 > 6)
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
void queue_command(Game* myGame){

if(PS2_X > PS2_HIGH_THRESHOLD){ //queue up rotate right command
		ps2_rotate_right = true;
}	
else if(PS2_X < PS2_LOW_THRESHOLD){ //queue up rotate left command
	ps2_rotate_left = true;
}

if(PS2_Y > PS2_HIGH_THRESHOLD){ //queue up an accelerate command
		ps2_accerlate = true;
}	
}

//*****************************************************************************
//*****************************************************************************
void initialize_hardware(void)
{
  init_serial_debug(true, true);
	lp_io_init(); //initialize Launchpad LED's and Push Buttons
	ps2_initialize(); //initialize GPIO pins connected PS2 Joystick
	lcd_config_gpio(); //initialize GPIO pins connected to LCD display
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

bool new_highscore(Game* myGame){
	//TODO
	return false;
}

void draw_main_menu(void) {
	char buffer1[10] = "Welcome to";
	char buffer2[10] = "Asteroids!";
	char buffer3[10] = "Touch to:";
	char buffer4[16] = "Start a New Game";
	char buffer5[10] = "Check the High Score";
	lcd_print_stringXY(buffer, 6, 9, TEXT_COLOR, BACKGROUND_COLOR);
}

int menu_pressed(void) { //return 1 if new game pressed; return 2 if high score pressed; return 0 otherwise
	
}

void mode_fsm() {
	Bullet newBullet;
	
	switch (mode) {
		
		case MAIN_MENU:{
			draw_main_menu();	//prints the main menu
			switch (menu_pressed()) {
				case 1:
					mode = IN_GAME;
					main_game = new_game();
					break;
				case 2:
					mode = DISPLAY_HIGH_SCORE;
					break;
				default:
					mode = MAIN_MENU;
			}
		}
		break;
		case IN_GAME:
			if (main_game->status == LOSE || main_game->status == WIN){		
					if(new_highscore(main_game)) 		
							mode = DISPLAY_HIGH_SCORE;
				
						else mode = MAIN_MENU;		
			}
			else {
					queue_command(main_game);
					lcd_clear_screen(LCD_COLOR_BLACK);
					if(io_down_pressed){
						newBullet = new_bullet(&(main_game->ship), main_game->bullets->time);
						fire_bullet((main_game->bullets), &newBullet);
					}
					update_game(main_game);
					draw_game(main_game);
			}
		break;
			
		case DISPLAY_HIGH_SCORE:
			
		break; 
		
		
		default:
			mode = MAIN_MENU;
	}
	
	
}


int	main(void)
{
	int count;
  initialize_hardware();

  put_string("\n\r");
  put_string("************************************\n\r");
  put_string("ECE353 - Fall 2016 HW3\n\r  ");
  put_string(group);
  put_string("\n\r     Name:");
  put_string(individual_1);
  put_string("\n\r     Name:");
  put_string(individual_2);
  put_string("\n\r");  
  put_string("************************************\n\r");

		lcd_config_screen(); //reset lcd screen
		lcd_clear_screen(LCD_COLOR_BLACK); //clear LCD screen to black
	
 
	
  // Reach infinite loop
  while(1){
		if (TIMERB_ALERT) {
				
				TIMERB_ALERT = false; //clear flag
		}
		if (TIMERA_ALERT) {
				sw1_pressed = sw1_debounce_fsm(); //check if debounced sw1 has been pressed
				TIMERA_ALERT = false; //clear flag
		}
		if (ALERT_ADC_UPDATE) {
			PS2_X = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract X value
			PS2_Y = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract Y value
			ALERT_ADC_UPDATE = false;
		}
		
		mode_fsm(); //99.9% of game occurs within mode_fsm
				
  };
}
