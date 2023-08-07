#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *file1;
	FILE *file2;
	FILE * destination;
	
	char filename[10];
	char c1;
	char c2;
	
	printf("\nEnter 1st file to be read: ");
	scanf("%s", filename);
	
	file1 = fopen(filename, "r");
	
	printf("\nEnter 2nd file to be read: ");
	scanf("%s", filename);
	
	file2 = fopen(filename, "r");
	
	printf("\nEnter file to be written: ");
	scanf("%s", filename);
	
	destination = fopen(filename, "w+");
	
	c1 = fgetc(file1);
	c2 = fgetc(file2);
	
	while( c1 != EOF || c2 != EOF){
		while(c1 != '\n'){
			fputc(c1, destination);
			c1 = fgetc(file1);
		}
		fputc(' ', destination);
		c1 = fgetc(file1);
		while(c2 != '\n'){
			fputc(c2, destination);
			c2 = fgetc(file2);
		}
		fputc('\n', destination);
		c2 = fgetc(file2);
	}
	
	if(c1 == EOF){
		while(c2 != EOF){
			fputc(c2, destination);
			c2 = fgetc(file2);
		}
	}
	else if(c2 == EOF){
		while(c1 != EOF){
			fputc(c1, destination);
			c1 = fgetc(file1);
		}
	}
	
	fclose(file1);
	fclose(file2);
	fclose(destination);
	
}
