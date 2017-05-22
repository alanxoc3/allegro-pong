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

	long counter = 0;
	
	while(1){
		al_clear_to_color(al_map_rgb(0,0,0));

		drawBoard();

		al_flip_display();

		printf("%ld\n", counter);
		counter++;
		al_rest( 1.0 / FPS);
	}

	al_destroy_display(display);

	return 0;
}
