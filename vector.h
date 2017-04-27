//author: Justin Gutter
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.1415926
#define LCD_MAX_X 239
#define LCD_MAX_Y 319
#define LCD_MIN 0


typedef struct { //define vector structure for other modules
	int x, y;
	} Vector;

Vector new_vector(void); //create and initialize vector struct
	
//function to perform vector addition
Vector add(Vector a, Vector b);

	//function to perform vector subtraction: VectorA - VectorB
Vector sub(Vector a, Vector b);
	
//function to perform scalar multiplication on a vector
Vector mult(Vector a, int scalar);
	
	
#endif

	