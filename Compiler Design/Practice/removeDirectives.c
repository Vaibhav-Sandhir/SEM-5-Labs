#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	FILE* source = fopen("input_2.c", "r");
	FILE* destination = fopen("input_3.c", "w");
	char c;
	c = fgetc(source);
	long position;
	int main_flag = 0;
	
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
		if(c == 'm'){
			c = fgetc(source);
			if(c == 'a'){
				c = fgetc(source);
				if(c == 'i'){
					c = fgetc(source);
					if(c == 'n'){
						c = fgetc(source);
						if(c == '('){
							main_flag = 1;
						}
					}
				}
			}
		}
		fseek(source, position, SEEK_SET);
		if(main_flag){
			fputc('m', destination);
			c = fgetc(source);
			while(c != EOF){
				fputc(c, destination);
				c = fgetc(source);
			}
			break;
		}
		
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
	fclose(source);
	fclose(destination);
	source = fopen("input_3.c", "r");
	destination = fopen("input_4.c", "w");
	char line[512];
	
	while(fgets(line, 512, source)){
		if(strlen(line) == 1)
			continue;
		fputs(line, destination);	
	}
}	
