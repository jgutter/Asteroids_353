
#ifndef __GAME_H__
#define __GAME_H__

#include "vector.h"
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"

typedef enum { WIN, LOSE, PAUSE, PLAYING} game_status;

typedef struct {
	Asteroid_list* asteroids;
	Ship ship;
	Bullet_Manager* bullets;
	int score;
	int lives;
	game_status status;
} Game;

Game* new_game(void); //create a new game

void delete_game(Game *); //free a game and other malloc'd dependencies

void update_game(Game*); //update game level events (game state)

void pause_game(Game*);

void update_game_ship(Game*); //update the ship

void update_particles(Game*); //update asteroids & bullets

void draw_game(Game*); //draw game

void draw_hud(Game*); //draw hud (score & lives)

void draw_win(Game*); //draw win text

void draw_lose(Game*); //draw lose text


#endif
