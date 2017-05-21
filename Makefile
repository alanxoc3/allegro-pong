# A pretty make file for a pretty game.

pong: main.c drawing.o
	$(CC) -Wall -pedantic -std=c99 -o pong $^ -lallegro -lallegro_main

drawing.o: pong_header.h drawing.c
	$(CC) -Wall -pedantic -std=c99 -c drawing.c

clean:
	rm *.o
