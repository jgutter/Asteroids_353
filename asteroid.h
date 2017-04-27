
#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "vector.h"
#include "lcd.h"
#define ASTEROIDS_LIST_SIZE 128


typedef struct {
	Vector position;
	Vector vector;
	int angle;
	uint8_t size;
} Asteroid

Asteroid new_asteroid(Vector pos, Vector vel);

typedef struct {
	Asteroid asteroids[MAX_ASTEROIDS];
	int start_index;
	int end_index;
} Asteroid_list //List of Asteroids (circular array)

//add asteroid to list
void add_asteroid(Asteroid_list* list, Asteroid * asteroid);

void remove_asteroid(Asteroid_list* list, Asteroid

Asteroid_list* new_asteroid_list(void); //dynamically allocate an asteroid list

void free_asteroid_list(Asteroid_list*); //free memory for asteroid list

void update_asteroid(Asteroid_list* asteroid);

void draw_asteroid(Asteroid_list* asteroid);


#endif
