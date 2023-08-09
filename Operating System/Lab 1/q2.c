#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc <= 1){
		printf("\nInsufficent Arguments");
		exit(1);
	}
	
	FILE* file1 = fopen(argv[1], "r");
	FILE* file2 = fopen(argv[2], "r");
	char line[256];
	
	if(file1 == NULL || file2 == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	
	int count = 0;
	
	while(1){
		if(fgetc(stdin) != '\0')
			count = 0;
		
		while(count < 20 && fgets(line, 256, file1)){
			puts(line);
			count++;
		}
		if(fgetc(stdin) != '\0'){
			count = 0;
			while(count < 20 && fgets(line, 256, file2)){
				puts(line);
				count++;
			}
		}
	}	
}
