#include <stdio.h>
#include <stdlib.h>

void main(){
	FILE *fptr1;
	int number_of_characters = 0;
	int number_of_lines = 0;
	
	char filename[10];
	char c;
	
	printf("\nEnter filename: ");
	scanf("%s", filename); 
	
	fptr1 = fopen(filename, "r");
	
	if(fptr1 == NULL)
		exit(0);
	
	c = fgetc(fptr1);
	
	while(c != EOF){
		if(c == '\n')
			number_of_lines++;
		else
			number_of_characters++;
		c = fgetc(fptr1);			
	}
	
	fclose(fptr1);
	
	printf("\n Number of characters are : %d",number_of_characters);
	printf("\n Number of lines are : %d\n", number_of_lines);	
	return;
}
