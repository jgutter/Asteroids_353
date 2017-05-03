//author: Justin Gutter
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159
#define LCD_MAX_X 249
#define LCD_MAX_Y 329
#define LCD_MIN -5
#define LCD_DRAW_MIN 0
#define LCD_DRAW_MAX_X 239
#define LCD_DRAW_MAX_Y 319


typedef struct { //define vector structure for other modules
	float x, y;
	} Vector;

Vector new_vector(void); //create and initialize vector struct
	
//function to perform vector addition
Vector add(Vector a, Vector b);

	//function to perform vector subtraction: VectorA - VectorB
Vector sub(Vector a, Vector b);
	
//function to perform scalar multiplication on a vector
Vector mult(Vector a, int scalar);

void wrap(Vector* a); //wrap vector within screen bounds
	
#endif

	