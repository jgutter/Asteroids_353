
#include "bullet.h"

/*
** bullet bit map
*/

const uint8_t bullet[] =
{
	0xC0,
	0xC0
};

const uint8_t bullet_canvas[] =
{
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00
};

Bullet* new_bullet(Ship * ship, float time_created){
	Bullet*	bullet;
	bullet = (Bullet*) malloc(sizeof(Bullet));
	bullet->velocity.y = (float) sin(PI * (ship->angle / 180));
	bullet->velocity.x = (float) cos(PI * (ship->angle / 180));
	bullet->position = ship->position;
	bullet->velocity = mult(bullet->velocity, BULLET_VELOCITY_FACTOR);
	bullet->lifetime = BULLET_LIFETIME;
	bullet->time_created = time_created;
	return bullet;
};

Bullet_Manager* new_bullet_manager(void) {
	Bullet_Manager * list;
	list = malloc(sizeof(Bullet_Manager));
	list->size = MANAGER_SIZE;
	list->end_index = 0;
	list->start_index = 0;
	list->time = 0;
	return list;
};

void fire_bullet(Bullet_Manager* list, Ship* ship) {
	Bullet* b = new_bullet(ship, list->time);
	list->bullets[list->end_index % list->size] = b;
	list->end_index++;
}

void remove_bullet(Bullet_Manager* list, Bullet * bullet) {
	draw_canvas_bullet(bullet);
	free(bullet);
	list->start_index++;	
};

bool bullet_manager_full(Bullet_Manager* list) {
	if(list->end_index - list->start_index == CLIP_SIZE)
		return true;
	else
		return false;
}

Asteroid * bullet_hit(Bullet_Manager* bm, Asteroid_list* al) {
	uint16_t i;
	uint16_t j;
	uint8_t asteroid_width, asteroid_height;
	int collisionX, collisionY;
	for(i = bm->start_index; i < bm->end_index; i++) {
		Bullet* bullet = bm->bullets[i % bm->size];
		for(j = al->start_index; j < al->end_index; j++) {
			Asteroid* asteroid = al->asteroids[j];
			if (asteroid->index < 0)
				continue;
			collisionX = asteroid->position.x - bullet->position.x;
			collisionY = asteroid->position.y - bullet->position.y;
			switch (asteroid->size) {
				case 0:
							asteroid_width = LARGE_ASTEROID_WIDTH;
							asteroid_height = LARGE_ASTEROID_HEIGHT;
							break;
				case 1:
							asteroid_width = MEDIUM_ASTEROID_WIDTH;
							asteroid_height = MEDIUM_ASTEROID_HEIGHT;
							break;
				case 2:
							asteroid_width = SMALL_ASTEROID_WIDTH;
							asteroid_height = SMALL_ASTEROID_HEIGHT;
			}
			if((fabs(collisionX) <= (asteroid_width/ 2)) && (fabs(collisionY) <= (asteroid_height / 2))) {
				remove_bullet(bm, bullet);
				return asteroid;
			}
		}
	}
	return NULL;
};

void update_bullets(Bullet_Manager* list, float dt) {
	uint16_t i;
	Bullet* bullet;
	for (i = list->start_index; i < list->end_index; i++) {
		bullet = list->bullets[i % list->size];
		if (list->time - bullet->time_created > bullet->lifetime) { //remove bullet if it has exceeded its lifetime
			draw_canvas_bullet(bullet);
			remove_bullet(list,bullet);
				continue;
		}
		bullet->position = add(bullet->position,bullet->velocity);
		wrap(&bullet->position);
	}
	list->time+= dt; //update current time in bullet manager
}

void draw_canvas_bullet(Bullet* bullet) {
	uint16_t prev_posX, prev_posY;
	prev_posX = bullet->position.x - bullet->velocity.x - 2;
	prev_posY = bullet->position.y - bullet->velocity.y - 2;
	lcd_draw_image(prev_posX, CANVAS_SIZE, prev_posY, CANVAS_SIZE, bullet_canvas, BACKGROUND_COLOR, BACKGROUND_COLOR);
}

void draw_bullets(Bullet_Manager* list) {
	uint16_t i;
	Bullet* b;
	for (i = list->start_index; i <list->end_index; i++) {
		b = list->bullets[i % list->size];
		draw_canvas_bullet(b);
		if((b->position.x > LCD_DRAW_MIN && b->position.x < LCD_DRAW_MAX_X) && (b->position.y > LCD_DRAW_MIN && b->position.y < LCD_DRAW_MAX_Y))
			lcd_draw_image(list->bullets[i % list->size]->position.x,BULLET_SIZE,list->bullets[i % list->size]->position.y,BULLET_SIZE,bullet,BULLET_COLOR, BACKGROUND_COLOR);
	}
};



