#ifndef __BULLET_H__
#define __BULLET_H__


#include "vector.h"
#include "asteroid.h"
#include "ship.h"

#define CLIP_SIZE 10
#define MANAGER_SIZE 64
#define BULLET_LIFETIME 1.5
#define BULLET_VELOCITY_FACTOR 100 //may need to be adjusted
#define BULLET_SIZE	1
#define BULLET_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK
typedef struct {
	Vector position;
	Vector velocity;
	float angle;
	float lifetime;
	float time_created;
} Bullet;

Bullet new_bullet(Ship* ship, float time_created);

typedef struct {
	Bullet * bullets;
	int start_index;
	int end_index;
	uint16_t size;
	float time;
} Bullet_Manager; //List of list (using FIFO circular array)

Bullet_Manager * new_bullet_manager(void); //dynamically allocate bullet manager list

void free_bullet_manager(Bullet_Manager* list); //free bullet_manager list

void fire_bullet(Bullet_Manager* list, Bullet* bullet); //add bullet to list

void remove_bullet(Bullet_Manager* list, Bullet * bullet); //remove bullet from list 

bool bullet_manager_full(Bullet_Manager *); //returns true if bullet manager is full (ammo on cooldown)

void update_bullets(Bullet_Manager* list, float);

Asteroid * bullet_hit(Bullet_Manager*, Asteroid_list*);

void draw_bullets(Bullet_Manager* list); 

#endif

