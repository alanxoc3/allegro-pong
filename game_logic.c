#include "pong_header.h"

void updatePaddlesForEvent(const ALLEGRO_EVENT * const event, Paddle *left_pad){

		// right side		
		int UP_KEY = ALLEGRO_KEY_UP;
		int DOWN_KEY = ALLEGRO_KEY_DOWN;

		// if left side
		if(left_pad->side == LEFT){
			UP_KEY = ALLEGRO_KEY_W;
			DOWN_KEY = ALLEGRO_KEY_S;
		}

		if( event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == UP_KEY){
				left_pad->yspd = -PADDLE_SPEED;
			} else if(event->keyboard.keycode == DOWN_KEY){
				left_pad->yspd = PADDLE_SPEED;
			}
		} else if(event->type == ALLEGRO_EVENT_KEY_UP){
			if((event->keyboard.keycode == UP_KEY && left_pad->yspd < 0) || (event->keyboard.keycode == DOWN_KEY && left_pad->yspd > 0)){	
				left_pad->yspd = 0;
				ALLEGRO_KEYBOARD_STATE key_state;
				al_get_keyboard_state(&key_state);
				if(al_key_down(&key_state, UP_KEY)){
					left_pad->yspd = -PADDLE_SPEED;	
				} else if(al_key_down(&key_state,DOWN_KEY)){
					left_pad->yspd = PADDLE_SPEED;
				}
			}
		}
}

void updatePaddle(Paddle * const left_pad){

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

