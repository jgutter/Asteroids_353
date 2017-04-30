
#ifndef __GAME_H__
#define __GAME_H__

#include "vector.h"
#include "asteroid.h"
#include "ship.h"
#include "bullet.h"
#include "ece353_hw2_fonts.h"

typedef enum { WIN, LOSE, PAUSE, PLAYING} game_status;

typedef struct {
	Asteroid_list* asteroids;
	Ship ship;
	Bullet_Manager* bullets;
	int score;
	int lives;
	game_status status;
	double current_time;
} Game;

Game* new_game(void); //create a new game

void delete_game(Game *); //free a game and other malloc'd dependencies

void update_game(Game*, float); //main game update to perform vector calculations

void pause_game(Game*);

void update_game_ship(Game*, float); //update the ship

void draw_game(Game*); //draw game

void draw_hud(Game*); //draw hud (score & lives)

void draw_win(Game*); //draw win text

void draw_paused(Game*);

void draw_lose(Game*); //draw lose text


#endif
