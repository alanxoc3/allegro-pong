// The awesome main loop file.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>
#include "pong_header.h"

static ALLEGRO_DISPLAY *display = NULL;

void allegro_init() {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		exit(-1);
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		exit(-1);
	}

	// In drawing.c, exits if there was an error.
	fonts_init();

	display = al_create_display(SCR_W, SCR_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		exit(-1);
	}

	audio_init();
}

int main(){
	allegro_init();
	
	int counter = 0;
	Paddle left_pad, right_pad;
	left_pad.side = LEFT;
	right_pad.side = RIGHT;
	left_pad.ypos = right_pad.ypos = SCR_H / 2 - PADDLE_HEIGHT / 2;
	left_pad.yspd = right_pad.yspd = 0;

	Ball ball;
	ball.xpos = 100;
	ball.ypos = 100;
	ball.xspd = BALL_INIT_SPEED;
	ball.yspd = BALL_INIT_SPEED;
	ball.radius = 10;

	Scores scores;
	scores.l = scores.r = 0;

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());

	play_music();
	
	while(1){
		al_clear_to_color(al_map_rgb(0,0,0));

		ALLEGRO_EVENT event;
		if(al_get_next_event(queue, &event)){
			updatePaddlesForEvent(&event, &left_pad);
			updatePaddlesForEvent(&event, &right_pad);
		}

		moveBall(&ball);
		updatePaddles(&left_pad, &right_pad);
		updateBallPaddleCollisions(&ball, &left_pad, &right_pad);
		updateBallWallCollisions(&ball, &scores);

		drawBoard();
		drawPaddle(&left_pad);
		drawPaddle(&right_pad);
		drawBall(&ball);

		drawScore(LEFT, scores.l);
		drawScore(RIGHT, scores.r);

		al_flip_display();

		counter++;
		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);
	audio_destroy();

	return 0;
}
