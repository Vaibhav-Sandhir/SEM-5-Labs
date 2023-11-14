#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define FIFO_NAME "/tmp/my_fifo"
#define MAX 5

void main(){
	int pipe_fd;
	int result;
	int count = 0;
	
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	
	if(pipe_fd == -1){
		printf("\nCould not open pipe");
		exit(1);
	}
	
	else{
		while(1){
			char action[4];
			result = read(pipe_fd, action, sizeof(action));
			
			if(result == -1){
				printf("\nCould not read pipe");
				exit(1);
			}
			
			if(strcmp(action, "add") == 0 && count < 5){
				printf("\nItem added count is %d", count);
				count++;
			}
			
			else if(count > 0){
				count--;
				printf("\nItem removed count is %d", count);
			}
			else{
				printf("\nNo item found");
			}
			usleep(3000);
		}
		close(pipe_fd);	
	}
}
