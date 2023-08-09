#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 3 ){
		printf("\nWrong number of arguments");
		exit(1);
	}
	
	int n = strlen(argv[2]);
	char substring[n];
	strcpy(substring, argv[2]);
	
	FILE * file1 = fopen(argv[1], "r");
	
	if(file1 == NULL){
		printf("\nError occured in opening file");
		exit(0);
	}
	
	char line[256];
	int line_number = 1;
	
	while(fgets(line, 256, file1)){
		if(strstr(line, substring) != NULL){
			printf("\nLine : %d  %s", line_number, line);
		}
		line_number++;
	}
}
