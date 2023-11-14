#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#define FIFO_NAME "/tmp/my_fifo"
#define MAX 5

void main(){
	 int pipe_fd;
	 int result;
	 
	 if(access(FIFO_NAME, F_OK) == -1){
	 	result = mkfifo(FIFO_NAME, 0777);
	 	if(result != 0){
	 		printf("\nCould not create fifo");
	 		exit(1);
	 	}
	 }
	 printf("hello");
	 pipe_fd = open(FIFO_NAME, O_WRONLY);
	 
	 if(pipe_fd == -1){
	 	printf("\nCould not open pipe");
	 	exit(1);
	 }
	 
	 else{
	 	while(1){
	 		printf("hello");
	 		result = write(pipe_fd, "add", sizeof("add"));
	 		if(result == -1){
	 			printf("\nCOuld not write on pipe");
	 			exit(1);
	 		}
	 		usleep(5000000);
	 	}
	 	close(pipe_fd);
	 }
}
