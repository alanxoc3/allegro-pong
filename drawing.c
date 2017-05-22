#include "pong_header.h"

void drawScore(const int xpos, const int score) {

}

void drawBoard() {

}

void drawBall(const Ball * const ball) {

}

drawPaddle(pl1);

void drawPaddle(Paddle pad);

void drawPaddle(const Paddle * const pad) {
	int x1, x2;
	const int paddle_width = 15;
	const int paddle_height = 40;
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	if(pad->side == LEFT){
		x = 0;
	} else {
		x = SCR_W - paddle_width;
	}

	al_draw_filled_rectangle(x1, pad->ypos, x2, pad->ypos + paddle_height, white);
}
