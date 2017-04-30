
#include "game.h"

#define NEW_GAME_LIVES 3
#define ASTEROID_NUMBER 4
#define SCREEN_CENTER_X 120
#define SCREEN_CENTER_Y 160
#define TEXT_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK
#define HUD_LEFT_MARGIN 210 //may need to be adjusted
#define HUD_SCORE_Y 280
#define HUD_LIVES_Y 260

Game* new_game(void) {
	Vector screen_center;
	Game* game;
	screen_center.x = SCREEN_CENTER_X;
	screen_center.y = SCREEN_CENTER_Y;
	game = (Game*) malloc(sizeof(Game));
	game->asteroids = NULL;
	game->bullets = new_bullet_manager();
	game->lives = NEW_GAME_LIVES;
	game->score = 0;
	game->current_time = 0;
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
	g->status = PAUSE;
};

void update_game(Game* game, float dt) {
	if (game->status == PAUSE)
		pause_game(game);
	if(game->status != PLAYING)
		return;
	
	update_asteroid(game->asteroids);
	update_bullets(game->bullets, dt);
	update_game_ship(game, dt);
	game->current_time += dt;
};

void update_game_ship(Game* g, float dt) {
	if (g->ship.invincibility > 0)
		g->ship.invincibility -= dt;
	else {
		if (ship_asteroid_collision(&g->ship,g->asteroids)) {  //if ship collides with an asteroid
			g->lives--;																					//lose a life
			g->ship.invincibility = SHIP_INVINCIBILITY;					//grant invincibility
			g->ship.position.x = SCREEN_CENTER_X;								//reset ship to center of screen
			g->ship.position.y = SCREEN_CENTER_Y;
			g->ship.velocity = new_vector();										//Zero ship's velocity
			g->ship.angle = RESET_ANGLE;
		}
	}
	update_ship(&g->ship);
};

void draw_game(Game*g) {
	
	draw_asteroids(g->asteroids);
	draw_bullets(g->bullets);
	draw_ship(&g->ship);
	draw_hud(g);
};

void draw_hud(Game* g) {
	int lives = g->lives;
	uint16_t x, y;
	lcd_draw_image(
	
	
};

void draw_win(Game* g) {
	char win_text[] = "You Won!";
	lcd_print_stringXY(win_text,SCREEN_CENTER_X,SCREEN_CENTER_Y, TEXT_COLOR, BACKGROUND_COLOR);
};

void draw_paused(Game* g) {
	char pause_text[] = "PAUSED";
	lcd_print_stringXY(pause_text,SCREEN_CENTER_X,SCREEN_CENTER_X, TEXT_COLOR, BACKGROUND_COLOR);
}

void draw_lose(Game* g) {
	char lose_text[] = "You Lose";
	lcd_print_stringXY(lose_text,SCREEN_CENTER_X, SCREEN_CENTER_Y, TEXT_COLOR, BACKGROUND_COLOR);
}

