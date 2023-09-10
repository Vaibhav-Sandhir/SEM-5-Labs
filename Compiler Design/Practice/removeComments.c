#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *source = fopen("input.c", "r");
	FILE *destination = fopen("input_1.c", "w");
	char c;
	long position;
	c = fgetc(source);
	
	while(c != EOF){
		if(c == '"'){
			fputc('"', destination);
			c = fgetc(source);
			while(c != '"'){
				fputc(c, destination);
				c = fgetc(source);
			}
		}
		
		if(c == '/'){
			position = ftell(source);
			c = fgetc(source);
			if(c == '/'){
				while(c != '\n')
					c = fgetc(source);
			}
			else if(c == '*'){
				c = fgetc(source);
				while(c != '*' && fgetc(source) != '/');
				c = fgetc(source);	
			}
			else{
				fputc('/',destination);
				fseek(source, position, SEEK_SET);
			}
		}
		fputc(c, destination);
		c = fgetc(source);
	}
	fclose(source);
	fclose(destination);
}
