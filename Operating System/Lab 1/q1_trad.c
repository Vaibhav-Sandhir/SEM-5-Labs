#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("\nWrong number of arguments");
		exit(1);
	}
	
	char filename[256];
	char substring[256];
	
	strcpy(filename, argv[1]);
	strcpy(substring, argv[2]);
	
	int fd = open(filename, O_RDONLY);
	
	if(fd == -1){
		printf("\nError in opening file");
		exit(1);
	}
	
	char buffer[256];
	int i = 0;
	
	while(read(fd, &buffer[i], 1) > 0){
		while(buffer[i] != '\n'){
			i++;
			read(fd, &buffer[i], 1);
		}
		if(strstr(buffer, substring) != NULL){
			write(1, buffer, strlen(buffer));
			printf("\n");
		}
		i = 0;
		memset(buffer, 0, sizeof(buffer));
	}	
}
