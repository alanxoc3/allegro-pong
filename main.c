// The awesome main loop file.

#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>


int main(){
	ALLEGRO_DISPLAY *display = NULL;

	al_init();

	display = al_create_display(640, 480);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	long counter = 0;
	
	while(1){
		printf("%ld\n", counter);
		counter++;
		al_rest(1/30.0);
	}

	return 0;
}
