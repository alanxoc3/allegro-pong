#include "pong_header.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GREEN al_map_rgb(0, 100, 0)
#define GRAY al_map_rgb(150, 150, 200)

#define FONT_FILE "res/invasion2000.ttf"

// Local to only drawing things.
static ALLEGRO_FONT *font = NULL;

void fonts_init() {
	// Addons needed for cool fonts.
	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font(FONT_FILE, 72, 0);

	if (!font){
		fprintf(stderr, "Could not load cool font.\n");
		exit(-1);
	}
}

void drawScore(const int xpos, const int score) {
	al_draw_text(font, GRAY, xpos, 400, ALLEGRO_ALIGN_CENTRE, "24");
}

void drawBoard() {
	const float x = SCR_W / 2;
	const float y = SCR_H / 2;
	const float rad = SCR_H / 8;

	al_draw_line(x, 0, x, y-rad, GREEN, 5);
	al_draw_line(x, y+rad, x, SCR_H, GREEN, 5);
	al_draw_circle(x, y, rad, GREEN, 5);
}

void drawBall(const Ball * const ball) {
	al_draw_filled_circle(ball->xpos, ball->ypos, ball->radius, GREEN);
	al_draw_circle(ball->xpos, ball->ypos, ball->radius, GRAY, 5);
}

void drawPaddle(const Paddle * const pad) {
	int x1 = 0, x2 = 0;
	const int paddle_width = 10;
	const int paddle_height = 80;

	if(pad->side == LEFT){
		x1 = 0;
	} else {
		x2 = SCR_W - paddle_width;
	}

	x2 = x1 + paddle_width;

	al_draw_filled_rectangle(x1, pad->ypos, x2, pad->ypos + paddle_height, GRAY);
}
