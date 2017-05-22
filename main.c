// The awesome main loop file.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>
#include "pong_header.h"

int main(){
	ALLEGRO_DISPLAY *display = NULL;

	al_init();

	display = al_create_display(SCR_W, SCR_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	Paddle left_pad;
	left_pad.side = LEFT;
	left_pad.ypos = 0;

	al_install_keyboard();
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());

	while(1){
		al_clear_to_color(al_map_rgb(0,0,0));

		ALLEGRO_EVENT event;
		bool a = al_get_next_event(queue, &event);
		if(a && event.type == ALLEGRO_EVENT_KEY_DOWN){
			if(event.keyboard.keycode == ALLEGRO_KEY_UP){
				left_pad.ypos += 5;
			} else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN){
				left_pad.ypos -= 5;
			}
		}

		drawBoard();
		drawPaddle(&left_pad);

		al_flip_display();

		//printf("%ld\n", counter);
		//counter++;
		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);

	return 0;
}
