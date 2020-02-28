all: gameoflife.o libgol.so
	gcc -o gameoflife gameoflife.c libgol.so -Wall -Wextra -pedantic -std=c11 -lm

libgol.so:
	gcc -shared -o libgol.so -fPIC gol.c -lm
	

gameoflife.o:
	gcc -c gameoflife.c

clean:
	rm -rf gameoflife gol.os gameoflife.o