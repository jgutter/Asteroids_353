

#include "vector.h"
#include "asteroid.h"

#define CLIP_SIZE 10
#define MANAGER_SIZE 64
#define BULLET_LIFETIME 1.5
#define BULLET_SPEED 100 //may need to be adjusted

typedef struct {
	Vector position;
	Vector velocity;
	float angle;
	float lifetime;
	float time_created;
} Bullet;

Bullet new_bullet(Vector pos, Vector vel, float angle, float lifetime, float time_created);

typedef struct {
	Bullet * bullets;
	int start_index;
	int end_index;
	uint16_t size;
} Bullet_manager; //List of list (using FIFO circular array)

Bullet_manager * new_bullet_manager(void); //dynamically allocate bullet manager list

void free_bullet_manager(Bullet_manager* list); //free bullet_manager list

void fire_bullet(Bullet_manager* list, Bullet* bullet); //add bullet to list

void remove_bullet(Bullet_manager* list, Asteroid * asteroid); //remove bullet from list 

bool bullet_manager_full(Bullet_manager *); //returns true if bullet manager is full (ammo on cooldown)

void draw_bullets(Bullet_manager* list); 

#endif

