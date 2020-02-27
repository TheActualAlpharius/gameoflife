#include<stdio.h>
#include <stdlib.h>
#include"gol.h"

int main(int argc, char *argv[]){

	int stats = 0;
	int torus = 0;
	char *inFileN;
	char *outFileN;
	char *nog = NULL;
	int guse = 0;
	int inuse = 0;
	int outuse = 0;
	for(int i = 1; i < argc; i++){
		if(argv[i][0] != '-') continue;
		switch (argv[i][1]){
			case 'i':
				if(inuse && inFileN != argv[i+1]){
					fprintf(stderr, "Improper commandline arguments");
					exit(0);
				}
				inuse = 1;
				inFileN = argv[i+1]; 
				break;
			
			case 'o':
				if(outuse && outFileN != argv[i+1]){
					fprintf(stderr, "Improper commandline arguments");
					exit(0);
				}
				outuse = 1;
				outFileN = argv[i+1];
				break;
			
			case 'g':
				if(guse && *nog != atoi(argv[i+1])){
					fprintf(stderr, "Improper commandline arguments");
					exit(0);
				}
				guse = 1;
				nog = argv[i+1];
				break;
			
			case 's':  stats = 1;
			break;
			
			case 't':  torus = 1;
			break;
			
			default:
			fprintf(stderr, "Error invalid commandline argument");
			exit(1);
		
		}
	}
	int nogInt = 5;
	int zerocheck = 0;
	if(nog != NULL){
		for(int i = 0; i < sizeof(nog)/sizeof(char); i++){
			if(nog[i] == '0'){
				zerocheck = 1;
			}
		}
		nogInt = atoi(nog);
	}
	if(nogInt == 0 && zerocheck != 0){
		fprintf(stderr, "Error invalid commandline argument");
		exit(1);
	}
	struct universe v;
	FILE *inFile = stdin;
	FILE *outFile = stdout;
	if(inuse){
		inFile = &*fopen(inFileN, "r");
	}
	read_in_file(inFile, &v);
	if(outuse){
		outFile = &*fopen(outFileN, "w");
	}
	for(int i = 0; i < nogInt; i++){
		if(torus){
			evolve(&v,will_be_alive_torus);
		}else{
			evolve(&v,will_be_alive);
		}
	}
	write_out_file(outFile,&v);
	if(stats){
		print_statistics(&v);
	}
return 0;
}