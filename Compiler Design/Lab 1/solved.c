#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *fptr1, *fptr2;

	char filename[10];
	char c;

	printf("\nEnter the filename for reading: ");
	scanf("%s", filename);

	fptr1 = fopen(filename, "r");

	if(fptr1 == NULL)
		exit(0);

	printf("\nEnter the filename for writing: ");
	scanf("%s",filename);

	fptr2 = fopen(filename, "w+");

	c = fgetc(fptr1);

	while(c != EOF){
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}	

	fclose(fptr1);
	fclose(fptr2);

}
