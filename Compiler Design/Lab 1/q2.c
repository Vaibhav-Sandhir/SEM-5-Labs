#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *source;
	FILE *destination;
	char filename[20];
	char c;
	long size;
	
	printf("\nEnter filename to be read: ");
	scanf("%s", filename);
	source = fopen(filename, "r");
	
	if(source == NULL)
		exit(0);
	
	printf("\nEnter filename to be written: ");
	scanf("%s", filename);
	destination = fopen(filename, "w+");
	
	fseek(source, 0, SEEK_END);
	size = ftell(source);
	
	c = fgetc(source);
	
	for(int i = 0; i < size; i++){
		fseek(source, size - 1 - i, SEEK_SET);
		c = fgetc(source);
		fputc(c, destination);
	}
	fclose(source);
	fclose(destination);
		 
}
