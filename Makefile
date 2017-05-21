# a pretty make file for a pretty game.

pong: main.c drawing.o
	$(CC) -std=c99 -o pong $^ -lallegro

drawing.o: pong_header.h drawing.cpp
	$(CC) -std=c99 -c drawing.cpp

clean:
	rm *.o
