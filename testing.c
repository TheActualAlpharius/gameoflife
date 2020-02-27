#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *nog = "-i 1234";
	int nogInt = 5;
	if(nog != NULL){
		nog++;
		nog++;
		int zerocheck = 1;
		for(int i = 0; i < sizeof(nog)/sizeof(char); i++){
			if(nog[i] != '0'){
				zerocheck = 0;
			}
		}
		nogInt = atoi(nog);
	}
	printf("%d\n", nogInt);
	return 0;
}