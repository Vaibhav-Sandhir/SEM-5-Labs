#include <stdio.h>
#include <stdlib.h>

void main(){
	char c;
	char source_file[256];
	char destination_file[256];
	FILE* source;
	FILE* destination;
	
	printf("\nEnter file to be read: ");
	scanf("%s", source_file);
	source = fopen(source_file, "r");
	
	printf("\nEnter file to be written: ");
	scanf("%s", destination_file);
	destination = fopen(destination_file, "w");
	
	if(source == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	
	c = fgetc(source);
	
	while(c != EOF){
	
		if(c == ' '){
			c = fgetc(source);
			while(c == ' '){
				c = fgetc(source);
			}
			fputc(' ', destination);
		}
		
		if(c == '\t'){
			fputc(' ', destination);	
		}
		
		else{
			fputc(c, destination);
		}
		
		c = fgetc(source);
	}
}
