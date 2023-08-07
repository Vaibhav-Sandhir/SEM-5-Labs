#include <stdio.h>
#include <stdlib.h>

void main(){
	char input;
	char line[256];
	char filename[256];
	FILE* file1;
	printf("\nEnter Filename: ");
	scanf("%s", filename);
	file1 = fopen(filename, "r");
	
	if(file1 == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	
	while(1){
		printf("Enter Q to quit or C to continue : ");
		scanf("%c", &input);
		
		if(input == 'Q'){
			exit(1);
		}
		
		else if(input == 'C'){
			int counter = 0;
			while(counter < 5){
				if(fgets(line, 256, file1) == NULL)
					exit(1);
					
				printf("%s", line);
				counter++;
			}
		}	
			
		else{
			printf("\nInvalid Input");
		}	
		
	}
}
