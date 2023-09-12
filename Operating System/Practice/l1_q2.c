#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

void main(int argc, char* argv[]){
	assert(argc == 2);
	
	char buffer[256];
	int i = 0;
	int count = 0;
	int fd = open(argv[1], O_RDONLY);
	
	if(fd < 0){
		perror("open");
		exit(-1);
	}
	
	while(count < 20){
		while(read(fd, &buffer[i], 1) > 0){
			while(buffer[i] != '\n'){
				i++;
				read(fd, &buffer[i], 1);
			}
			write(1, buffer, strlen(buffer));
			i = 0;
			memset(buffer, 0, sizeof(buffer));
			count++;
			while(count == 20 && fgetc(stdin) != '\0'){
				count = 0;
			}
		}
	}
}
