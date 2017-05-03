//author: Justin Gutter

#ifndef __SHIP_H__
#define __SHIP_H__

#include "vector.h"
#include "lcd.h"
#include "asteroid.h"

#define MAX_SPEED 5 //max speed will need to be adjusted

#define SHIP_INVINCIBILITY 5 //ship will be invincibile for 1 second on a new life

#define ACCELERATION_CONST 1 //acceleration constant for accelerating

#define ROTATE_INCR 10 //ship will rotate in 10 degree increments
#define RESET_ANGLE 90

#define BITMAP_REF 	36	//for properly indexing into bitmap array
#define SHIP_WIDTH 24 	
#define SHIP_HEIGHT 24
#define CANVAS_WIDTH 30
#define CANVAS_HEIGHT 30


#define SHIP_COLOR LCD_COLOR_WHITE
#define INVINCIBILE_SHIP LCD_COLOR_YELLOW
#define BACKGROUND_COLOR LCD_COLOR_BLACK

typedef struct {
	
	Vector position; //position of ship
	
	Vector velocity; //velocity of ship
	
	float angle;				//angle of ship in degrees
	
	float invincibility;	//seconds of invincibility
	
} Ship;

Ship new_ship(Vector pos, Vector vel); //create a new ship at a position with a velocity

void accelerate_ship(Ship* ship); //accelerate ship

void rotate_ship_left(Ship* ship); //rotate ship left

void rotate_ship_right(Ship* ship); //rotate ship right

bool ship_asteroid_collision(Ship* ship, Asteroid_list* al); //detect if ship has collided with an asteroid

void update_ship(Ship * ship); //update ship's position vector

void draw_ship(Ship * ship); //draw ship to LCD screen

#endif