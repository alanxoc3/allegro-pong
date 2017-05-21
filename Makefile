# A pretty make file for a pretty game.

pong: main.c drawing.o
	$(CC) -std=c11 -o pong $^ -lallegro -lallegro_main

drawing.o: pong_header.h drawing.c
	$(CC) -std=c11 -c drawing.c

clean:
	rm *.o
