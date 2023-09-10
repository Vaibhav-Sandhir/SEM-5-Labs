#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE* source = fopen("input_3.c", "r");
	FILE* destination = fopen("input_4.c", "w");
	char c;
	c = fgetc(source);
	long position;
	
	while(c != EOF){
		position = ftell(source);
		if(c == '"'){
			fputc('"', destination);
			c = fgetc(source);
			while(c != '"'){
				fputc(c, destination);
				c = fgetc(source);
			}
		}
		position = ftell(source);
		
		if(c == '\n'){
			fputc('\n', destination);
			c = fgetc(source);
			if(c == '#'){
				while(c != '\n')
					c = fgetc(source);
			}
			else if(c == ' '){
				c = fgetc(source);
				if(c != '#'){
					fputc(' ', destination);
				}
				else{
					while(c != '\n')
						c = fgetc(source);
				}
			}
		}
		fputc(c, destination);
		c = fgetc(source);
	}
	
}
