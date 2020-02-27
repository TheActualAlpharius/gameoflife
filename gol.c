#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gol.h"

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
	struct universe newU;
	newU.rows = u->rows;
	newU.columns = u->columns;
	newU.current_alive = u->current_alive;
	newU.average_alive = u->average_alive;
	newU.universe = malloc(newU.rows * newU.columns * sizeof(char));
	int aliveC = 0;
	int alive;
	for(int row = 0; row < u->rows; row ++){
		for(int col = 0; col < u->columns; col ++){
			alive = (rule)(u, col, row);
			if(alive){
				newU.universe[row * newU.columns + col] = '*';
				aliveC++;
			}
			else{
				newU.universe[row * newU.columns + col] = '.';
			}
		}
	}
	for(int i = 0; i < u->rows * u->columns; i++){
		u->universe[i] = newU.universe[i];
	}
	u->current_alive = aliveC;
	u->average_alive = newU.average_alive * u->evolveC + aliveC;
	u->evolveC++;
	u->average_alive /= u->evolveC;
}

void read_in_file(FILE *infile, struct universe *u){
	if (infile == NULL){
		//give error no file exists
		fprintf(stderr, "File not found");
		exit(1);
	}
	u->rows = 0;
	u->columns = 0;
	int columns = 0;
	int rows = 0;
	int counter = 0;
	int aliveC = 0;
	int firstRow = 1;
	u->universe = malloc(1 * sizeof(char));
	char next;
	while((next = fgetc(infile)) != EOF){
		//next is some character a character
		if(next == '*' || next == '.'){
			if(firstRow){
				columns++;
			}
			if(next == '*'){
				aliveC++;
			}
			counter++;
			char *newuni;
			newuni = realloc(u->universe, counter * sizeof(char));
			u->universe = newuni;
			u->universe[counter-1] = next;
			//still 1
		}else if(next == '\n'){
			firstRow = 0;
			rows++;
			if(counter != (rows * columns)){
				//too many or too few chars in row
				fprintf(stderr, "File is not a grid");
				
			}
		}else {
			//got bad input
			exit(1);
		}
	}
	rows++;
	if(counter != (rows * columns)){
		//too many or too few chars
		fprintf(stderr, "File is not a grid");
		exit(1);
	}
	u->rows = rows;
	u->columns = columns;
	u->evolveC = 1;
	u->current_alive = aliveC / counter;
	u->average_alive = u->current_alive;
}

void write_out_file(FILE *outfile, struct universe *u){
	for(int row = 0; row < u->rows; row++){
		for(int col = 0; col < u->columns; col++){
			fprintf(outfile, "%c", u->universe[u->columns * row + col]);
		}
		fprintf(outfile, "\n");
	}
}

int is_alive(struct universe *u, int column, int row){
	char check = u->universe[row * u->columns + column];
	if (check == '*'){
		return 1;
	}else if(check == '.'){
		return 0;
	}
	exit(1);
	
}

int will_be_alive(struct universe *u, int column, int row){
	int c = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			if(x == 0 && y == 0){
				continue;
			}
			if(row + x < 0 || row + x >= u->rows || column + y < 0 || column + y >= u->columns){
				continue;
			}
			if(is_alive(u, column + y, row + x)){
				c ++;
			}
		}
	}
	if(c == 3){
		return 1;
	}else if(c == 2 && is_alive(u, column, row)){
		return 1;
	}
	return 0;
}

void print_statistics(struct universe *u){
	float current = u->current_alive * 1000;
	current = round(current);
	current /= 1000;
	printf("%.3f%% of cells currently alive\n", current);
	
	float average = u->average_alive * 1000;
	average = round(average);
	average /= 1000;
	printf("%.3f%% of cells alive on average\n", average);
}

int will_be_alive_torus(struct universe *u,  int column, int row){
	int c = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			if(x == 0 && y == 0){
				continue;
			}
			if(is_alive(u, ((column + y + u->columns) % u->columns), ((row + x + u->rows) % u->rows))){
				c ++;
			}
		}
	}
	if(c == 3){
		return 1;
	}else if(c == 2 && is_alive(u, column, row)){
		return 1;
	}
	return 0;
}




