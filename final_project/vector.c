//author: Justin Gutter

#include "vector.h"

//initialize a new vector struct
Vector new_vector() {
	Vector vector;
	vector.x = 0;
	vector.y = 0;
	return vector;
}

//function to perform vector addition
Vector add(Vector a, Vector b) {
	Vector sum = new_vector();
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return sum;
};

//function to perform vector subtraction: VectorA - VectorB
Vector sub(Vector a, Vector b) {
	Vector result = new_vector();
	result.x = a.x - b.x;
	result.y = b.y - b.y;
	return result;
};

//function to perform scalar multiplication on a vector
Vector mult(Vector a, int scalar) {
	Vector result = new_vector();
	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return result;
};

void wrap(Vector* b) {
	if(b->x > LCD_MAX_X)
		b->x = LCD_MIN;
	else if (b->x < LCD_MIN)
		b->x = LCD_MAX_X;
	
	if (b->y > LCD_MAX_Y)
		b->y = LCD_MIN;
	else if (b->y < LCD_MIN)
		b->y = LCD_MAX_Y;
};

