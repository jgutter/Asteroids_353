#ifndef __asteroid__
#define __asteroid__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "lcd.h"


#define       LCD_X_MAX     239
#define       LCD_X_MIN      0
#define				LCD_Y_MAX			319
#define				LCD_Y_MIN			0

#define				CONST_X_VEL		0
#define 			CONST_Y_VEL		0

#define 			LARGE_WIDTH		56
#define 			LARGE_HEIGHT	50
#define 			MED_WIDTH 		28
#define 			MED_HEIGHT 		25 
#define 			SMALL_WIDTH		8
#define 			SMALL_HEIGHT	13

#define				LARGE_AST			2
#define 			MED_AST				1
#define				SMALL_AST			0

/* Font data for Sitka Small 12pt */
extern const uint8_t asteroidBitmaps[];

extern int screen_map[240][40];	//external array that holds all used screen pixels 

typedef struct
{
  uint16_t Xpos;				//current X coordinate on LCD
  uint16_t Ypos;				//current Y coordiante on LCD
	uint8_t Xvelocity;	//rotational velocity
	uint8_t Yvelocity;	//translational velocity 
	uint8_t size;				//three different valid values for different sizes
											//0=small 1=medium 2=big	
	uint8_t isDead;			//indicates if ship is hit 
} asteroid;


/**********************************************************
* Function Name: initialize_asteroid
**********************************************************
* Summary: initializes asteroid with give size at a 
* random empty location.
*
* Returns: true if successful
**********************************************************/
bool initialize_asteroid(asteroid* myAsteroid, uint8_t size);
	


/**********************************************************
* Function Name: lcd_print_asteroid
**********************************************************
* Summary: prints given asteroid with foreground color as fg_color
* and background color as bg_color
*
* Returns:
*  Nothing
**********************************************************/
void lcd_print_asteroid(
		asteroid * myAsteroid,
    uint16_t fg_color, 
    uint16_t bg_color
);



/**********************************************************
* Function Name: lcd_print_asteroid
**********************************************************
* Summary: prints given asteroid 
*
*
* Returns:
*  Nothing
**********************************************************/
void move_asteroid(asteroid * myAsteroid);
    
#endif