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
	
	Paddle left_pad;
	left_pad.side = LEFT;
	left_pad.ypos = 0;
	left_pad.yspd = 0;

	Ball ball;
	ball.xpos = 100;
	ball.ypos = 100;
	ball.radius = 10;

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());

	play_music();
	
	while(1){
		al_clear_to_color(al_map_rgb(0,0,0));

		ALLEGRO_EVENT event;
		bool a = al_get_next_event(queue, &event);
		if(a && event.type == ALLEGRO_EVENT_KEY_DOWN){
			if(event.keyboard.keycode == ALLEGRO_KEY_UP){
				left_pad.yspd = -10;
			} else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
				left_pad.yspd = 10;
			}
		} else if(a && event.type == ALLEGRO_EVENT_KEY_UP){
			if((event.keyboard.keycode == ALLEGRO_KEY_UP && left_pad.yspd < 0) || (event.keyboard.keycode == ALLEGRO_KEY_DOWN && left_pad.yspd > 0)){	
				left_pad.yspd = 0;
				ALLEGRO_KEYBOARD_STATE key_state;
				al_get_keyboard_state(&key_state);
				if(al_key_down(&key_state, ALLEGRO_KEY_UP)){
					left_pad.yspd = -10;	
				} else if(al_key_down(&key_state, ALLEGRO_KEY_DOWN)){
					left_pad.yspd = 10;
				}

			}
		}

		int PADDLE_HEIGHT = 80;
		if(left_pad.yspd != 0){
			left_pad.ypos += left_pad.yspd;
			if(left_pad.ypos < 0){
				left_pad.yspd = 0;
			} else if(left_pad.ypos > SCR_H - PADDLE_HEIGHT){
				left_pad.ypos = SCR_H - PADDLE_HEIGHT;
			}
		}

		drawBoard();
		drawPaddle(&left_pad);
		drawBall(&ball);
		drawScore(LEFT, 4);
		drawScore(RIGHT, 4);

		al_flip_display();

		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);
	audio_destroy();

	return 0;
}
