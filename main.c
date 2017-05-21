
#include <allegro5/allegro.h>
#include <time.h>


int main(){
	al_init();
	long counter = 0;
	
	while(1){
		printf("%ld\n", counter);
		counter++;
		al_rest(1/30.0);
	}

	return 0;
}
