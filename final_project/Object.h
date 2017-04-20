//author: Justin Gutter

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "vector.h"
#include <stdbool.h>

#define MAX_OBJECTS 128 //limit max number of objects to 128

typedef struct {
	
	Vector position;		//position of object
	
	Vector velocity;		//velocity of object
	
	float lifetime; 		//lifetime of object
	
	float time_created; //time object was created
	
	bool alive;					//if object is alive
	
} Object;

typedef struct {
	Object objects[MAX_OBJECTS]; //array of objects
	
	float time; //current time relative to creation of Object_list
} Object_list;

Object_list* new_object_list(void); //dynamically allocate an object list

void free_list(Object_list*); //free dynamically allocated object list

void add_object(Object_list* object_list, Vector pos, Vector vel, float lifetime); //add an object to object_list

void draw_objects(Object_list*); //draw objects in list to lcd screen; using draw_image function

#endif
