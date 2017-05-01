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

#define CURSOR_HEIGHT				1
#define	CURSOR_WIDTH				1
#define CENTERED_X					120
#define CENTERED_Y					160

#define BACKGROUND_COLOR		LCD_COLOR_BLACK
#define LCD_X_MAX						239
#define LCD_Y_MAX						319
#define LCD_X_MIN						0
#define LCD_Y_MIN						0

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

bool sw1_pressed;
bool sw2_pressed;
bool io_down_pressed;
volatile bool ALERT_ADC_UPDATE; 	//Update PS2 ADC values; triggered by TimerB
volatile bool TIMERB_ALERT; 			//Timer B ISR flag
volatile bool TIMERA_ALERT;				//Timer A ISR flag

static int count_B = 0; 					//private variable to count number of  Timer B interrupts
static int count_A = 0; 					//private variable to count number of Timer A interrupts

bool blue_LED_on = false;					//Blue LED boolean value used by TimerA ISR
bool green_LED_on = false;				//Green LED boolean value used by TimerB ISR

int X_pos = CENTERED_X;						//X position of cursor; initialized to middle of X-axis
int Y_pos = CENTERED_Y;						//Y position of cursor; initialized to middle of Y-axis

int oldX_pos = CENTERED_X;											//old X coordinate for MOVE mode re-drawing
int oldY_pos = CENTERED_Y;											//old Y coordinate for MOVE mode re-drawing

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
void MOVE_SHIP(Game* myGame){

//if the x direction of joystick is holding a voltage higher than  three quarters of maximum, 
//increment the x postion, if at the extremity, then wrap	
if(PS2_X > PS2_HIGH_THRESHOLD){
		if (PS2_Y > PS2_LOW_THRESHOLD && PS2_Y < PS2_HIGH_THRESHOLD)
					oldY_pos = Y_pos;					//update old Y position when not moving diagonally
		oldX_pos = X_pos; //save old position
		if((X_pos + 1) > LCD_X_MAX)
					X_pos = LCD_X_MIN;		
		else  X_pos++; 
}	

//if the x direction of joystick is holding a voltage lower than quarter of maximum, 
//decrement the x postion, if at the lower extremity, then wrap
else if(PS2_X < PS2_LOW_THRESHOLD){
		if (PS2_Y > PS2_LOW_THRESHOLD && PS2_Y < PS2_HIGH_THRESHOLD)
					oldY_pos = Y_pos;
		oldX_pos = X_pos;  //save old position
		if((X_pos - 1) < LCD_X_MIN)
					X_pos = LCD_X_MAX;
		else 	X_pos--; 
}
//if the y direction of joystick is holding a voltage higher than three quarters of maximum, 
//increment the y postion, if at the extremity, then wrap	
if(PS2_Y > PS2_HIGH_THRESHOLD){
		if (PS2_X > PS2_LOW_THRESHOLD && PS2_X < PS2_HIGH_THRESHOLD)
				oldX_pos = X_pos;
	oldY_pos = Y_pos;  //save old position
	Y_pos++;
	if(Y_pos > LCD_Y_MAX)
		Y_pos = LCD_Y_MIN;
}	

//if the y direction of joystick is holding a voltage lower than quarter of maximum, 
//decrement the y postion, if at the lower extremity, then wrap
else if(PS2_Y < PS2_LOW_THRESHOLD){
		if (PS2_X > PS2_LOW_THRESHOLD && PS2_X < PS2_HIGH_THRESHOLD)
				oldX_pos = X_pos;
		oldY_pos = Y_pos;  //save old position
	
		Y_pos--;
		if(Y_pos < LCD_Y_MIN)
			Y_pos = LCD_Y_MAX;
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

void mode_fsm(Game* myGame) {
	Bullet newBullet;
	
	switch (mode) {
		
		case MAIN_MENU:{
			welcome_screen();	//prints the main menu
		
			if (start_pressed())
					mode = GAME;
			
			else if(highscore_pressed())
					mode = HIGH_SCORE; 
		
					
			}
		break;
			
		case GAME:
			if (myGame->status == LOSE){		
					if(new_highscore(myGame)) 		mode = HIGH_SCORE;
				
						else mode = MAIN_MENU;		
			}
			else {
					lcd_clear_screen(LCD_COLOR_BLACK);
				
					MOVE_SHIP(myGame);	//update ship
					if(){
						newBullet = new_bullet(&(myGame->ship), BULLET_LIFETIME, curr_time);
						fire_bullet((myGame->bullets), &newBullet);
					}
					
					update_game(myGame);
					draw_game(myGame);
					
				if (!lp_io_read_pin(SW2_BIT)) { //erase mode
						lcd_draw_image(oldX_pos,CURSOR_WIDTH, oldY_pos, CURSOR_HEIGHT, cursor, BACKGROUND_COLOR,BACKGROUND_COLOR);
						screen_map[oldX_pos][oldY_pos] = 0;
					}
					else {			//move mode
							if (screen_map[oldX_pos][oldY_pos] == 1) {
									lcd_draw_image(oldX_pos,CURSOR_WIDTH, oldY_pos, CURSOR_HEIGHT, cursor, LCD_COLOR_GREEN,BACKGROUND_COLOR);
							}else {
									lcd_draw_image(oldX_pos,CURSOR_WIDTH, oldY_pos, CURSOR_HEIGHT, cursor, BACKGROUND_COLOR,BACKGROUND_COLOR);
							}
					}
			}
		break;
			
		case HIGH_SCORE:
			
		break; 
		
		
		default:
		mode = MAIN_MENU; //default into DRAW state if fsm goes into an unexpected state
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
				if (count_B == 9) { //toggle green LED every 10 TimerB ISR executions
				green_LED_on = !green_LED_on;
				if (green_LED_on)
				lp_io_set_pin(GREEN_BIT);
				else
				lp_io_clear_pin(GREEN_BIT);
				count_B = 0;
				} else {	//if 10 executions has not occured; increment count & turn off green LED
				count_B++;
				}
				TIMERB_ALERT = false; //clear flag
		}
		if (TIMERA_ALERT) {
				sw1_pressed = sw1_debounce_fsm(); //check if debounced sw1 has been pressed
				if (count_A == 9) { //toggle blue LED every 10 TimerA ISR executions
				blue_LED_on = !blue_LED_on;
					if (blue_LED_on)
						lp_io_set_pin(BLUE_BIT);
					else
						lp_io_clear_pin(BLUE_BIT);
					count_A = 0;
				} 
				else {	//if 10 executions has not occured; increment count & turn off blue LED
					count_A++;
				}
				TIMERA_ALERT = false; //clear flag
		}
		if (ALERT_ADC_UPDATE) {
			PS2_X = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract X value
			PS2_Y = ((ADC0_Type *)ADC0_BASE)->SSFIFO2 & 0xFFF; //extract Y value
			ALERT_ADC_UPDATE = false;
		}
		
		for(count = 0; count <100000; count++)
			{}
		
		MOVE_SHIP();
		mode_fsm();
			
			
  };
}
