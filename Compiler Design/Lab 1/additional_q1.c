#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	char filename[256];
	char line[256];
	char c;
	int blank_lines = 0;
	int blank_spaces = 0;
	int semicolon_lines = 0;
	FILE* file1;
	printf("\nEnter filename: ");
	scanf("%s", filename);
	file1 = fopen(filename, "r");
	
	if(file1 == NULL){
		printf("\nError in opening in file");
		exit(1);
	}
	
	while(fgets(line, 256, file1)){
		printf("%s", line);
		if(line[0] == '\n')
			blank_lines++;
	}
	
	rewind(file1);
	
	c = fgetc(file1);	
	while(c != EOF){
		if(c == ' '){
			blank_spaces++;
			}
			
		if(c == ';'){
			c = fgetc(file1);
			if(c == '\n')
				semicolon_lines++;
		}
		c = fgetc(file1);	
	}
	
	printf("\nNumber of blank lines - %d", blank_lines);
	printf("\nNumber of blank spaces - %d", blank_spaces);
	printf("\nNumber of lines ending with semicolon - %d", semicolon_lines);
}
