#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>

void main(int argc, char* argv[]){
	assert(argc == 3);
	
	char file[256];
	char substr[256];
	char buffer[256];
	int i = 0;
	strcpy(file, argv[1]);
	strcpy(substr, argv[2]);
	
	int fd = open(file, O_RDONLY);
	
	if(fd == -1){
		perror("open");
		exit(-1);
	}
	
	while(read(fd, &buffer[i], 1) > 0){
		while(buffer[i] != '\n'){
			i++;
			read(fd, &buffer[i], 1);
		}
		buffer[i] = '\0';
		if(strstr(buffer, substr) != NULL){
			write(1, buffer, strlen(buffer));
			printf("\n");
		}
		i = 0;
		memset(buffer, 0, sizeof(buffer));	
	}
}
