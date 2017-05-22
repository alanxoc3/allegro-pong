#include "pong_header.h"
#include <allegro5/allegro.h>

void drawScore(const int xpos, const int score) {

}

void drawBoard() {
	const float x = SCR_W / 2;
	const ALLEGRO_COLOR col = al_map_rgb(256, 100, 0);
	al_draw_line(x, 0, x, SCR_H, col, 5);
}

void drawBall(const Ball * const ball) {

}

void drawPaddle(const Paddle * const pad) {

}
