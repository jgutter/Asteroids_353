
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

void update_bullets(Bullet_Manager* list) {
	uint8_t i;
	for (i = list->start_index; i < list->end_index; i++) {
		if (list->time - list->bullets[i].time_created > list->bullets[i].lifetime) { //remove bullet if it has exceeded its lifetime
				remove_bullet(list,&list->bullets[i]);
				continue;
		}
		list->bullets[i].position = add(list->bullets[i].position,list->bullets[i].velocity);
		if (list->bullets[i].position.x > LCD_MAX_X) //wrap position
			list->bullets[i].position.x = LCD_MIN;
		else if (list->bullets[i].position.x < LCD_MIN)
			list->bullets[i].position.y = LCD_MAX_X;
		
		if(list->bullets[i].position.y > LCD_MAX_Y)
			list->bullets[i].position.y = LCD_MIN;
		else if (list->bullets[i].position.y < LCD_MIN)
			list->bullets[i].position.y = LCD_MAX_Y;
	}
	list->time++; //may want to use another method for updating manger's clock
}

void draw_bullets(Bullet_Manager* list) {
	uint8_t i;
	for (i = list->start_index; i <list->end_index; i++) {
		lcd_draw_image(list->bullets[i].position.x,BULLET_SIZE,list->bullets[i].position.y,BULLET_SIZE,bullet,BULLET_COLOR, BACKGROUND_COLOR);
	}
};



