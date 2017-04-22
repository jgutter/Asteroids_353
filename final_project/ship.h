#ifndef __ship__
#define __ship__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

#define       LCD_X_MAX     239
#define       LCD_X_MIN      0
#define				LCD_Y_MAX			319
#define				LCD_Y_MIN			0

#define				ANGLE_MAX			35
#define				ANGLE_MIN			0

/* Font data for Sitka Small 12pt */
extern const uint8_t shipBitmaps[];

typedef struct
{
	uint8_t angle; 			//holds the current angel that ship is pointing 
  uint8_t Xpos;				//current X coordinate on LCD
  uint8_t Ypos;				//current Y coordiante on LCD
  uint8_t Xvelocity;	//rotational velocity
	uint8_t Yvelocity;	//translational velocity 
	uint8_t isDead;			//indicates if ship is hit 
} ship;


/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
bool initialize_ship(ship* myShip, uint8_t angle, uint8_t Xpos, uint8_t Ypos, uint8_t Xvelocity, uint8_t Yvelocity);
	
/**********************************************************
* Function Name: lcd_print_stringXY
**********************************************************
* Summary: prints a string to the LCD screen at a specified
* XY location in specified foreground and background colors
* X will specify the number of characters across with X=0
* being the left most character position, and X=13 being
* the right most.  Y will specify the number of characters
* down the screen with Y=0 being the top of the screen and
* Y=19 being the bottom row of characters.  NOTE this is
* opposite of how columns and rows are specified for the
* IL9341.
* Returns:
*  Nothing
**********************************************************/
void lcd_print_ship(
		ship * myShip,
    uint16_t fg_color, 
    uint16_t bg_color
);

/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
void angle_increment(ship* myShip);
	
/**********************************************************
* Function Name: 
**********************************************************
* Summary: 
*
*
* Returns:
*  Nothing
**********************************************************/
void angle_decrement(ship* myShip);
    
#endif