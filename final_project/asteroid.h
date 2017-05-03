
#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "vector.h"
#include "lcd.h"
#include <stdlib.h>
#define ASTEROIDS_LIST_SIZE 64


#define LARGE_ASTEROID_HEIGHT	50
#define LARGE_ASTEROID_WIDTH	56
#define LARGE_CANVAS_HEIGHT 55
#define LARGE_CANVAS_WIDTH 61

#define MEDIUM_ASTEROID_HEIGHT	25
#define MEDIUM_ASTEROID_WIDTH	32
#define MEDIUM_CANVAS_HEIGHT 30
#define MEDIUM_CANVAS_WIDTH 37
#define MEDIUM_BITMASK_ADDRESS 350

#define SMALL_ASTEROID_HEIGHT	13
#define SMALL_ASTEROID_WIDTH	16
#define SMALL_CANVAS_HEIGHT 18
#define SMALL_CANVAS_WIDTH 21
#define SMALL_BITMASK_ADDRESS 450

#define ASTEROID_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK

#define SIZE_VELOCITY_FACTOR 1
#define BASE_VELOCITY 1

typedef struct {
	Vector position;
	Vector velocity;
	uint8_t size;		//size definition: 0 LARGE; 1 MEDIUM; 2 SMALL
	int index; //index of this asteroid in list
} Asteroid;

Asteroid* new_asteroid(Vector pos, Vector vel, uint8_t size);

typedef struct {
	Asteroid* asteroids[ASTEROIDS_LIST_SIZE];
	int start_index;
	int end_index;
	uint16_t list_size;
	int num_asteroids;
} Asteroid_list; //List of Asteroids (static array)

Asteroid_list* new_asteroid_list(void); //create a new asteroid list

void delete_asteroid_list(Asteroid_list*);

void add_asteroid(Asteroid_list* list, Asteroid* asteroid); //add asteroid to asteroid list

void remove_asteroid(Asteroid_list* list, Asteroid* asteroid); //remove asteroid from asteroid list

void update_asteroids(Asteroid_list* list); //update positions of Asteroids

void draw_canvas_asteroid(Asteroid*);

void draw_asteroids(Asteroid_list* list); //draw asteroids to screen

void split_asteroid(Asteroid_list * list, Asteroid*); //split asteroid (remove 1 asteroid and add two smaller ones into list)

int count_asteroid(Asteroid_list*); //returns number of asteroids remaining

#endif
