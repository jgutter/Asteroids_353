
#include "asteroid.h"

/*
** Asteroid bitmaps for different sized asteroids
		TODO
*/

const uint8_t asteroidBitmaps[] =
{
	0x00
};

Asteroid new_asteroid(Vector pos, Vector vel, uint16_t angle, uint8_t size) {
	Asteroid asteroid;
	asteroid.position = pos;
	vel.x += (size * SIZE_VELOCITY_FACTOR); //when splitting asteroid; only need new angle & decrement size
	vel.y += (size * SIZE_VELOCITY_FACTOR);
	asteroid.velocity = vel;
	asteroid.angle = angle;
	asteroid.size = size;
	return asteroid;
};

Asteroid_list* new_asteroid_list(void) {
	Asteroid_list * list;
	list->list_size = ASTEROIDS_LIST_SIZE;
	list->asteroids = (Asteroid*) malloc(sizeof(Asteroid)*list->list_size);
	list->start_index = 0;
	list->end_index = 0;
	list->num_asteroids = 0;
	return list;
};

void free_asteroid_list(Asteroid_list* list) { //free memory for asteroid list
	free(list->asteroids);
};

void add_asteroid(Asteroid_list* list, Asteroid * asteroid) {
	list->asteroids[list->end_index % list->list_size] = *asteroid;
	asteroid->index = list->end_index;
	list->end_index++;
	list->num_asteroids++;
}

void remove_asteroid(Asteroid_list* list, Asteroid* asteroid) {
	//
	//will be removing from an arbitrary place in array, will need to function 
	//such that draw and update can still operate as expected with gaps in array
	//set removed asteroid to NULL or set index < 0? Is start_index still needed?
	list->asteroids[asteroid->index].index = -1;
	list->num_asteroids--;
};

// split asteroid
void split_asteroid(Asteroid_list * list, Asteroid* asteroid){
	if(asteroid->size < 2) { //if asteroid is Large or medium
		Asteroid ast1 = new_asteroid(asteroid->position,asteroid->velocity,asteroid->angle,asteroid->size+1); //make 2 new asteroids
		Asteroid ast2 = new_asteroid(asteroid->position,asteroid->velocity,asteroid->angle,asteroid->size+1);
		Vector split_vel = new_vector();
		add_asteroid(list, &ast1); //first asteroid continues in same direction
		split_vel.x = asteroid->velocity.y;
		split_vel.y = asteroid->velocity.x;
		ast2.velocity = split_vel;
		add_asteroid(list,&ast2); //second asteroid continues in opposite direction
	}
	remove_asteroid(list,asteroid);
}

int count_asteroid(Asteroid_list* list) {
	return list->num_asteroids;
}
	
void update_asteroids(Asteroid_list* list) {
	uint8_t i;
	for(i = list->start_index; i < list->end_index; i++) {
		if (list->asteroids[i].index < 0)
			continue;
		list->asteroids[i].position = add(list->asteroids[i].position, list->asteroids[i].velocity);
		if (list->asteroids[i].position.x > LCD_MAX_X)
			list->asteroids[i].position.x = LCD_MIN;
		else if (list->asteroids[i].position.x < LCD_MIN)
			list->asteroids[i].position.x = LCD_MAX_X;
		
		if (list->asteroids[i].position.y > LCD_MAX_Y)
			list->asteroids[i].position.y = LCD_MIN;
		else if (list->asteroids[i].position.y < LCD_MIN)
			list->asteroids[i].position.y = LCD_MAX_Y;
	}
};

void draw_asteroids(Asteroid_list* list){
	uint8_t i;
	int img_index = 0;
	for(i = list->start_index; i < list->end_index; i++) {
		if (list->asteroids[i].index < 0)
			continue;
		switch (list->asteroids[i].size) {
			case 0: //large
				//ADD CODE calculate to index into bitmap array (for all three cases)
				lcd_draw_image(list->asteroids[i].position.x,LARGE_ASTEROID_WIDTH,list->asteroids[i].position.y,LARGE_ASTEROID_HEIGHT, &asteroidBitmaps[img_index],ASTEROID_COLOR, BACKGROUND_COLOR);
			case 1: //medium
				lcd_draw_image(list->asteroids[i].position.x,MEDIUM_ASTEROID_WIDTH,list->asteroids[i].position.y,MEDIUM_ASTEROID_HEIGHT, &asteroidBitmaps[img_index], ASTEROID_COLOR, BACKGROUND_COLOR);
			case 2: //small
				lcd_draw_image(list->asteroids[i].position.x,SMALL_ASTEROID_WIDTH, list->asteroids[i].position.y, SMALL_ASTEROID_HEIGHT, &asteroidBitmaps[img_index], ASTEROID_COLOR, BACKGROUND_COLOR);
		}
	}
};	

