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

void updatePaddlesForEvent(const ALLEGRO_EVENT * const event, Paddle *left_pad){

		// right side
		
		int UP_KEY = ALLEGRO_KEY_UP;
		int DOWN_KEY = ALLEGRO_KEY_DOWN;

		if(left_pad->side == LEFT){
			UP_KEY = ALLEGRO_KEY_W;
			DOWN_KEY = ALLEGRO_KEY_S;
		}

		if( event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == UP_KEY){
				left_pad->yspd = -10;
			} else if(event->keyboard.keycode == DOWN_KEY){
				left_pad->yspd = 10;
			}
		} else if(event->type == ALLEGRO_EVENT_KEY_UP){
			if((event->keyboard.keycode == UP_KEY && left_pad->yspd < 0) || (event->keyboard.keycode == DOWN_KEY && left_pad->yspd > 0)){	
				left_pad->yspd = 0;
				ALLEGRO_KEYBOARD_STATE key_state;
				al_get_keyboard_state(&key_state);
				if(al_key_down(&key_state, UP_KEY)){
					left_pad->yspd = -10;	
				} else if(al_key_down(&key_state,DOWN_KEY)){
					left_pad->yspd = 10;
				}

			}
		}
}

void updatePaddle(Paddle * const left_pad){

		int PADDLE_HEIGHT = 80;

		if(left_pad->yspd != 0){
			left_pad->ypos += left_pad->yspd;
			if(left_pad->ypos < 0){
				left_pad->yspd = 0;
			} else if(left_pad->ypos > SCR_H - PADDLE_HEIGHT){
				left_pad->ypos = SCR_H - PADDLE_HEIGHT;
			}
		}
}

void updatePaddles(Paddle * const  left_pad, Paddle * const right_pad){
	updatePaddle(left_pad);
	updatePaddle(right_pad);
}

void moveBall(Ball * const ball) {
	if (ball->ypos < 0 + ball->radius) {
		ball->yspd = -ball->yspd;
	} else if (ball->ypos > SCR_H - ball->radius) {
		ball->yspd = -ball->yspd;
	}

	if (ball->xpos < 0 + ball->radius) {
		ball->xspd = -ball->xspd;
	} else if (ball->xpos > SCR_W - ball->radius) {
		ball->xspd = -ball->xspd;
	}

	ball->xpos += ball->xspd;
	ball->ypos += ball->yspd;
}

int main(){
	allegro_init();
	
	int counter = 0;
	Paddle left_pad, right_pad;
	left_pad.side = LEFT;
	right_pad.side = RIGHT;
	left_pad.ypos = right_pad.ypos = 0;
	left_pad.yspd = right_pad.yspd = 0;

	Ball ball;
	ball.xpos = 100;
	ball.ypos = 100;
	ball.xspd = 80.0 / FPS;
	ball.yspd = 80.0 / FPS;
	ball.radius = 10;

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

		updatePaddles(&left_pad, &right_pad);
		moveBall(&ball);

		drawBoard();
		drawPaddle(&left_pad);
		drawPaddle(&right_pad);
		drawBall(&ball);
		drawScore(LEFT, counter / 15);
		drawScore(RIGHT, counter / 30);

		al_flip_display();

		counter++;
		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);
	audio_destroy();

	return 0;
}
