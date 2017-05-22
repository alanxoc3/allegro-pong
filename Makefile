# A pretty make file for a pretty game.

FLAGS=-lallegro -lallegro_main -lallegro_color -lallegro_primitives

pong: main.c drawing.o
	$(CC) -Wall -pedantic -std=c99 -o pong $^ $(FLAGS)

drawing.o: pong_header.h drawing.c
	$(CC) -Wall -pedantic -std=c99 -c drawing.c

clean:
	rm *.o
