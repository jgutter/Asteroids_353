
#include "game.h"

#define NEW_GAME_LIVES 3
#define ASTEROID_NUMBER 4

Game* new_game(void) {
	Vector screen_center;
	Game* game;
	screen_center.x = LCD_MAX_X / 2;
	screen_center.y = LCD_MAX_Y / 2;
	game = (Game*) malloc(sizeof(Game));
	game->asteroids = NULL;
	game->bullets = new_bullet_manager();
	game->lives = NEW_GAME_LIVES;
	game->score = 0;
	game->status = PLAYING;
	game->ship = new_ship(screen_center, new_vector());
	return game;
};

void delete_game(Game * game) {
	free_asteroid_list(game->asteroids);
	free_bullet_manager(game->bullets);
	free(game);
}

void pause_game(Game* g) {
	
};

void update_game(Game* game) {
	if (game->status == PAUSE)
		pause_game(game);
	if(game->status != PLAYING)
		return;
	
	
	
};

