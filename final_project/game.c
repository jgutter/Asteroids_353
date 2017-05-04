
#include "game.h"

#define NEW_GAME_LIVES 3
#define ASTEROID_NUMBER 4
#define SCREEN_CENTER_X 120
#define SCREEN_CENTER_Y 160
#define SCREEN_CENTER_STRING_X 4
#define SCREEN_CENTER_STRING_Y 9
#define TEXT_COLOR LCD_COLOR_WHITE
#define BACKGROUND_COLOR LCD_COLOR_BLACK
#define HUD_LEFT_MARGIN 1 //may need to be adjusted
#define HUD_SCORE_Y 1
#define HUD_LIVES_Y 2
#define ASTEROID_SCORE 100
#define LARGE_ASTEROID 0

Game* new_game(void) {
	Vector screen_center;
	Game* game;
	screen_center.x = SCREEN_CENTER_X;
	screen_center.y = SCREEN_CENTER_Y;
	game = (Game*) malloc(sizeof(Game));
	game->bullets = new_bullet_manager();
	game->lives = NEW_GAME_LIVES;
	game->score = 0;
	game->current_time = 0;
	game->status = PLAYING;
	game->ship = new_ship(screen_center, new_vector());
	game->asteroids = new_asteroid_list();
	spawn_asteroids(game);
	return game;
};

void spawn_asteroids(Game* g) {
	uint8_t i;
	Vector random_pos, random_vel;
	for (i = 0; i < ASTEROID_NUMBER; i++) {
		Asteroid* a;
		random_vel = new_vector();
		random_pos.y	= rand() % 320;
		random_pos.x  = rand() % 240;
		random_vel.x  = rand() % 2;
		if(i == 0)
			random_vel.x = -2;
		random_vel.y 	= rand() % 2;
		if (i == 1)
			random_vel.y = -2;
		a = new_asteroid(random_pos, random_vel, LARGE_ASTEROID);
		add_asteroid(g->asteroids,a);
	}
	return;
}

void delete_game(Game * game) {
	delete_asteroid_list(game->asteroids);
	free(game);
}

void pause_game(Game* g) {
	g->status = PAUSE;
	draw_paused(g);
};

void update_game(Game* game, float dt) {
	Asteroid * asteroid_hit;
	if (game->status == PAUSE)
		pause_game(game);
	if(game->status != PLAYING)
		return;
	
	update_asteroids(game->asteroids);
	update_bullets(game->bullets, dt);
	update_game_ship(game, dt);
	game->current_time += dt;
	
	asteroid_hit = bullet_hit(game->bullets,game->asteroids);
	if (asteroid_hit != NULL) {
		game->score += ASTEROID_SCORE + (asteroid_hit->size * (ASTEROID_SCORE/4)) +(ASTEROID_SCORE/game->current_time); //score based on time & asteroid size
		split_asteroid(game->asteroids, asteroid_hit);
	}
	if (game->lives < 0)
		game->status = LOSE;
	else if (count_asteroid(game->asteroids) == 0)
		game->status = WIN;
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
			lcd_clear_screen(BACKGROUND_COLOR);
		}
	}
	update_ship(&g->ship);
};

void draw_game(Game*g) {
	draw_hud(g);
	draw_ship(&g->ship);
	draw_asteroids(g->asteroids);
	draw_bullets(g->bullets);
	
};

void resume_game(Game*g) {
	char remove_pause[] = "PAUSED";
	g->status = PLAYING;
	lcd_print_stringXY(remove_pause,SCREEN_CENTER_STRING_X,SCREEN_CENTER_STRING_Y, BACKGROUND_COLOR, BACKGROUND_COLOR);
}

void draw_hud(Game* g) {
	char lives[10] = "Lives: ";
	char score_buffer[20] = "Score: ";
	char time_debug[20] = "Time: ";
	snprintf(score_buffer+7, (sizeof(char)*13), "%d", g->score);
	lcd_print_stringXY(score_buffer,HUD_LEFT_MARGIN,HUD_SCORE_Y,TEXT_COLOR, BACKGROUND_COLOR);
	snprintf(lives+7, (sizeof(char)*3), "%d", g->lives);
	lcd_print_stringXY(lives,HUD_LEFT_MARGIN,HUD_LIVES_Y, TEXT_COLOR, BACKGROUND_COLOR);
	snprintf(time_debug+6, (sizeof(char)*14), "%.2f", g->current_time);
	lcd_print_stringXY(time_debug,HUD_LEFT_MARGIN,3,TEXT_COLOR, BACKGROUND_COLOR);
};

void draw_win(Game* g) {
	char win_text[] = "You Won!";
	lcd_print_stringXY(win_text,SCREEN_CENTER_STRING_X,SCREEN_CENTER_STRING_Y, TEXT_COLOR, BACKGROUND_COLOR);
};

void draw_paused(Game* g) {
	char pause_text[] = "PAUSED";
	lcd_print_stringXY(pause_text,SCREEN_CENTER_STRING_X,SCREEN_CENTER_STRING_Y, TEXT_COLOR, BACKGROUND_COLOR);
}

void draw_lose(Game* g) {
	char lose_text[] = "You Lose";
	lcd_print_stringXY(lose_text,SCREEN_CENTER_STRING_X, SCREEN_CENTER_STRING_Y, TEXT_COLOR, BACKGROUND_COLOR);
}

