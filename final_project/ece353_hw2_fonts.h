#ifndef __ECE353_HW2_FONTS_H__
#define __ECE353_HW2_FONTS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

#define       FONT_HEIGHT     16
#define       FONT_WIDTH      17

/* Font data for Sitka Small 12pt */
extern const uint8_t sitkaSmall_12ptBitmaps[];

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
void lcd_print_stringXY(
    char *msg, 
    int8_t X,
		int8_t Y,
    uint16_t fg_color, 
    uint16_t bg_color
);
    
#endif
