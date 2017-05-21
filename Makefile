# A pretty make file for a pretty game.

pong: main.c drawing.o
	$(CC) -pedantic -std=c99 -o pong $^ -lallegro -lallegro_main

drawing.o: pong_header.h drawing.cpp
	$(CC) -pedantic -std=c99 -c drawing.cpp

clean:
	rm *.o
