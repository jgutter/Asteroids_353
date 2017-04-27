//author: Justin Gutter

#ifndef __SHIP_H__
#define __SHIP_H__

#include "vector.h"
#include "lcd.h"

#define MAX_SPEED 100 //max speed will need to be adjusted

#define SHIP_INVINCIBILITY 2 //ship will be invincibile for 2 seconds on a new life

#define ACCELERATION_CONST 5 //acceleration constant for thrusting and deceleration

#define ROTATE_INCR 10 //ship will rotate in 10 degree increments

#define SHIP_WIDTH 20 //may need to be adjusted
#define SHIP_HEIGHT 23

#define SHIP_COLOR LCD_COLOR_WHITE

#define BACKGROUND_COLOR LCD_COLOR_BLACK

typedef struct {
	
	Vector position; //position of ship
	
	Vector velocity; //velocity of ship
	
	int angle;				//angle of ship in degrees
	
	int invincibility;	//seconds of invincibility
	
} Ship;

Ship new_ship(Vector pos, Vector vel); //create a new ship at a position with a velocity

void accelerate_ship(Ship* ship); //accelerate ship

void rotate_ship_left(Ship* ship); //rotate ship left

void rotate_ship_right(Ship* ship); //rotate ship right

void update_ship(Ship * ship); //update ship's position vector

void draw_ship(Ship * ship); //draw ship to LCD screen

#endif