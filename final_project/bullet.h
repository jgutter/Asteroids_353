#ifndef __BULLET_H__
#define __BULLET_H__


#include "vector.h"
#include "asteroid.h"
#include "ship.h"

#define CLIP_SIZE 5
#define MANAGER_SIZE 32
#define BULLET_LIFETIME 1.5
#define BULLET_VELOCITY_FACTOR 8
#define BULLET_SIZE	2
#define BULLET_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK
#define CANVAS_SIZE 4

typedef struct {
	Vector position;
	Vector velocity;
	float lifetime;
	double time_created;
} Bullet;

Bullet* new_bullet(Ship* ship, float time_created);

typedef struct {
	Bullet* bullets[MANAGER_SIZE];
	int start_index;
	int end_index;
	uint16_t size;
	float time;
} Bullet_Manager; //List of list (using FIFO circular array)

Bullet_Manager * new_bullet_manager(void); //dynamically allocate bullet manager list

void fire_bullet(Bullet_Manager* list, Ship*); //add bullet to list

void remove_bullet(Bullet_Manager* list, Bullet * bullet); //remove bullet from list 

bool bullet_manager_full(Bullet_Manager *); //returns true if bullet manager is full (ammo on cooldown)

void update_bullets(Bullet_Manager* list, float); //update position of all bullets

Asteroid * bullet_hit(Bullet_Manager*, Asteroid_list*); //detect hit of a bullet and an asteroid; returns hit asteroid

void draw_bullets(Bullet_Manager* list); //draws bullets

void draw_canvas_bullet(Bullet*); //dedicated function for drawing canvas when bullet dies

#endif

