#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int n = argc - 1;
	int i = 0;
	while(i < n){
		int fd = open(argv[i + 1], O_RDONLY);
		if(fd == -1){
			printf("\nError in opening file");
			exit(1);
		}
		char buffer[256];
		int count = 0;
		int j = 0;
		while(read(fd, &buffer[j], 1) > 0){
			while(buffer[j] != '\n' && count < 20){
				j++;
				read(fd, &buffer[j], 1);
			}
			write(1, buffer, strlen(buffer));
			count++;
			j = 0;
			memset(buffer, 0, sizeof(buffer));
		}
		while(1){
			char c = fgetc(stdin);
			if(c != '\0')
				break;
		}
		i++;
	} 
}
