Files: gameoflife.c, gol.h, gol.c

all: gameoflife.o libgol.so
	gcc -o gameoflife gameoflife.c libgol.so -Wall -Wextra -pedantic -std=c11

lobgol.so:
	gcc -shared -o libgol.so -fPIC gol.c
	

gameoflife.o:
	gcc -c gameoflife.c

clean:
	rm -rf gameoflife gol.os gameoflife.o