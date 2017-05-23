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
	ball->xpos += ball->xspd;
	ball->ypos += ball->yspd;
}

void resetBall(Ball * const ball){
	// reset ball
	ball->xpos = 100;
	ball -> ypos = 100;
	ball -> yspd = BALL_INIT_SPEED;
	ball -> xspd = BALL_INIT_SPEED;
}

void updateBallWallCollisions(Ball * const ball, Scores * const scores){
	if (ball->ypos < 0 + ball->radius) {
		ball->yspd = -ball->yspd;
	} else if (ball->ypos > SCR_H - ball->radius) {
		ball->yspd = -ball->yspd;
	}

	if (ball->xpos < 0 + ball->radius){
		scores->r++;
		resetBall(ball);
	} else if(ball->xpos > SCR_W - ball->radius) {
		scores->l++;
		resetBall(ball);
	}

}


void updateBallPaddleCollision(Ball * const ball, Paddle * const pad, enum Side side){

	if(side == LEFT){
		//printf("left\n");
	} else {
		//printf("right\n");
	}
	
	bool x_touch = false;
	bool heading = false;

	if(side == LEFT){
		x_touch = ball->xpos - ball->radius <= PADDLE_WIDTH;
		heading = ball->xspd < 0;
	} else {
		x_touch = ball->xpos + ball->radius  >= (SCR_W - PADDLE_WIDTH);
		heading = ball->xspd > 0;
	}

	bool y_touch = ball->ypos >= pad->ypos && ball->ypos <= (pad->ypos + PADDLE_HEIGHT);
	if(heading && x_touch && y_touch){
		printf("HIT PADDLE \n");

		if(pad->yspd == 0){
			ball->xspd *= -1;
		} else {
			// pad moving up, makes ball move downwards
			// increase yspd, decrease xspd
			ball -> yspd -= (1/8.0) * pad->yspd;
			float dy = pow(ball->yspd, 2);
			ball -> xspd = sqrt((BALL_SPEED*BALL_SPEED) - dy);
			printf("ball speed: %f\n", BALL_SPEED);
			printf("DY: %f\n", dy);
			printf("x: %f\n", ball->xspd);
			printf("y: %f\n", ball->yspd);
		}

		//ball->xspd = -ball->xspd;
		//ball->yspd = -ball->yspd;

		ball->xpos += 2 * ball->xspd;

	}
}

// check if ball is touching paddle, and heading towards paddle
// if so, update ball trajectory
void updateBallPaddleCollisions(Ball * const ball, Paddle * const lp, Paddle * const rp){
	updateBallPaddleCollision(ball, lp, LEFT);
	updateBallPaddleCollision(ball, rp, RIGHT);
}


