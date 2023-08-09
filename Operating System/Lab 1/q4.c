#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("\nWrong number of arguments: ");
		exit(1);
	}
	
	int input = open(argv[1], O_RDONLY);
	int output = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR| S_IWUSR);
	
	if(input == -1){
		printf("\nError in opening file");
		exit(1);
	}
	
	char c;
	while(read(input, &c, 1) == 1){
		write(output, &c, 1);
	}
	
	close(input);
	close(output);
}
