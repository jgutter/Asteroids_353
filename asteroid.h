
#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "vector.h"
#include "lcd.h"
#include <stdlib.h>
#define ASTEROIDS_LIST_SIZE 128

//ADD CODE
#define LARGE_ASTEROID_HEIGHT	0
#define LARGE_ASTEROID_WIDTH	0
#define MEDIUM_ASTEROID_HEIGHT	0
#define MEDIUM_ASTEROID_WIDTH	0
#define SMALL_ASTEROID_HEIGHT	0
#define SMALL_ASTEROID_WIDTH	0
#define ASTEROID_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK

#define SIZE_VELOCITY_FACTOR 1
#define BASE_VELOCITY 16

typedef struct {
	Vector position;
	Vector velocity;
	uint16_t angle;
	uint8_t size;		//size definition: 0 LARGE; 1 MEDIUM; 2 SMALL
	int index; //index of this asteroid in list
} Asteroid;

Asteroid new_asteroid(Vector pos, Vector vel, uint16_t angle, uint8_t size);

typedef struct {
	Asteroid * asteroids;
	int start_index;
	int end_index;
	uint16_t list_size;
	int num_asteroids;
} Asteroid_list; //List of Asteroids (circular array)

Asteroid_list* new_asteroid_list(void); //dynamically allocate an asteroid list

void free_asteroid_list(Asteroid_list* list); //free memory for asteroid list

//add asteroid to list
void add_asteroid(Asteroid_list* list, Asteroid * asteroid); //add asteroid to asteroid list

void remove_asteroid(Asteroid_list* list, Asteroid * asteroid); //remove asteroid from asteroid list

void update_asteroids(Asteroid_list* list); //update positions of Asteroids

void draw_asteroids(Asteroid_list* list); //draw asteroids to screen

void split_asteroid(Asteroid_list * list, Asteroid*); //split asteroid (remove 1 asteroid and add two smaller ones into list)

int count_asteroid(Asteroid_list*); //returns number of asteroids remaining

#endif
