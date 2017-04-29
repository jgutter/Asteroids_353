
#include "bullet.h"

/*
** bullet bit map will go here (single pixel will do)
*/

const uint8_t bullet[] =
{
	0x80
};

Bullet new_bullet(Ship * ship, Vector pos, Vector vel, float angle, float lifetime, float time_created){
	Bullet bullet;
	bullet.velocity.y = (float) sin(PI * (ship->angle / 180));
	bullet.velocity.x = (float) cos(PI * (ship->angle / 180));
	bullet.position = ship->position;
	bullet.angle = 0;
	bullet.velocity = mult(bullet.velocity, BULLET_VELOCITY_FACTOR);
	bullet.lifetime = lifetime;
	bullet.time_created = time_created;
	return bullet;
};

Bullet_Manager* new_bullet_manager(void) {
	Bullet_Manager* list;
	list->size = MANAGER_SIZE;
	list->end_index = 0;
	list->start_index = 0;
	list->time = 0;
	list->bullets = (Bullet*) malloc(sizeof(Bullet)*list->size);
	return list;
};

void free_bullet_manager(Bullet_Manager* list) {
	free(list->bullets);
};

void fire_bullet(Bullet_Manager* list, Bullet* bullet) {
	list->bullets[list->end_index % list->size] = *bullet;
	list->end_index++;
}

void remove_bullet(Bullet_Manager* list, Bullet * bullet) {
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
	int asteroid_width, asteroid_height;
	Vector collision;
	for(i = bm->start_index; i < bm->end_index; i++) {
		Bullet bullet = bm->bullets[i % bm->size];
		for(j = al->start_index; j < al->end_index; j++) {
			Asteroid asteroid = al->asteroids[j];
			if (asteroid.index < 0)
				continue;
			collision = sub(bullet.position,asteroid.position);
			switch (asteroid.size) {
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
			if((fabs(collision.x) <= (asteroid_width / 2)) && (fabs(collision.y) <= (asteroid_height / 2))) {
				remove_bullet(bm, &bullet);
				return &al->asteroids[j];
			}
		}
	}
	return NULL;
};

void update_bullets(Bullet_Manager* list) {
	uint16_t i;
	Bullet bullet;
	for (i = list->start_index; i < list->end_index; i++) {
		bullet = list->bullets[i % list->size];
		if (list->time - bullet.time_created > bullet.lifetime) { //remove bullet if it has exceeded its lifetime
				remove_bullet(list,&list->bullets[i]);
				continue;
		}
		bullet.position = add(bullet.position,bullet.velocity);
		if (bullet.position.x > LCD_MAX_X) //wrap position
			bullet.position.x = LCD_MIN;
		else if (bullet.position.x < LCD_MIN)
			bullet.position.y = LCD_MAX_X;
		
		if(bullet.position.y > LCD_MAX_Y)
			bullet.position.y = LCD_MIN;
		else if (bullet.position.y < LCD_MIN)
			bullet.position.y = LCD_MAX_Y;
	}
	list->time++; //may want to use another method for updating manger's clock
}

void draw_bullets(Bullet_Manager* list) {
	uint16_t i;
	for (i = list->start_index; i <list->end_index; i++) {
		lcd_draw_image(list->bullets[i % list->size].position.x,BULLET_SIZE,list->bullets[i % list->size].position.y,BULLET_SIZE,bullet,BULLET_COLOR, BACKGROUND_COLOR);
	}
};



