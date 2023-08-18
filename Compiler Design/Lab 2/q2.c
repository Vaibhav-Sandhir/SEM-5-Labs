#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	char source_file[256];
	char destination_file[256];
	char c; 
	FILE* source;
	FILE* destination;
	
	printf("\nEnter filename to be read: ");
	scanf("%s", source_file);
	
	printf("\nEnter filename to be written: ");
	scanf("%s", destination_file);
	
	source = fopen(source_file, "r");
	destination = fopen(destination_file, "w");
	
	if(source == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	
	int flag = 1;
	c = fgetc(source);
	while(c != EOF){
		if(c == '"'){
			fputc(c, destination);
			c = fgetc(source);
			while(c != '"'){
				fputc(c, destination);
				c = fgetc(source);
			}
			fputc(c, destination);
			c = fgetc(source);
			continue;
		}
		
		if(c == '\n'){
			flag = 1;
		}
			
		else if(c == '#' && flag == 1){
			while(c != '\n'){
				c = fgetc(source);
				}
			c = fgetc(source);
			continue;	
		}
		
		else if(c != ' ' && c != '\t'){
			flag = 0;
		}
		fputc(c, destination);
		c = fgetc(source);
	}	
}
