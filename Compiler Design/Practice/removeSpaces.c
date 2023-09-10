#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	FILE* source = fopen("input_1.c", "r");
	FILE* destination = fopen("input_2.c", "w");
	char c;
	c = fgetc(source);
	
	while(c != EOF){
		if(c == '"'){
			c = fgetc(source);
			fputc('"', destination);
			while(c != '"'){
				fputc(c, destination);
				c = fgetc(source);
			}
		}
		if(c == ' '){
			c = fgetc(source);
			while(c == ' ')
				c = fgetc(source);
			fputc(' ', destination);		
		}
		else if(c == '\t'){
			fputc(' ', destination);
			c = fgetc(source);
			while(c == '\t')
				c = fgetc(source);
		}
		
		fputc(c, destination);
		c = fgetc(source);
	}
	fclose(source);
	fclose(destination);
	source = fopen("input_2.c", "r");
	destination = fopen("input_3.c", "w");
	char line[512];
	
	while(fgets(line, 512, source)){
		if(strlen(line) == 1)
			continue;
		fputs(line, destination);	
	}
}
