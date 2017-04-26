//author: Justin Gutter

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "vector.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "asteroid.h"

#define TYPE_SHIP		0
#define TYPE_ASTEROID 1
#define TYPE_LASER		2


#define MAX_OBJECTS 128 //limit max number of objects to 128


typedef struct {
	
	Vector position;		//position of object
	
	Vector velocity;		//velocity of object
	
	float lifetime; 		//lifetime of object
	
	float time_created; //time object was created
	
	bool alive;					//if object is alive
	
	int8_t type; 				//3 types to indicate the three 
											//object types we have, 0 = ship	1= asteroid 	2= laser
	
} Object;

typedef struct {
	Object objects[MAX_OBJECTS]; //array of objects
	int8_t last_free;						//the last empty array index 
	float time; //current time relative to creation of Object_list
} Object_list;

Object_list* new_object_list(void); //dynamically allocate an object list

void free_list(Object_list* object_list); //free dynamically allocated object list

bool add_object(Object_list* object_list, int8_t object_type, Vector pos, Vector vel, float lifetime); //add an object to object_list

void draw_objects(Object_list* object_life); //draw objects in list to lcd screen; using draw_image function

#endif
