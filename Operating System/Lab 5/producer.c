#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <assert.h>
#define BUFFER_SIZE PIPE_BUF //Max buffer size
#define TEN_MEG (1024 * 1024 * 10) // 10MB
#define FIFO_NAME "/home/student/Desktop/210905152_OS/fifo"

int main(){
	int pipe_fd;
	int bytes_sent = 0;
	int buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int result;
	if(access(FIFO_NAME, F_OK) == -1){
		result = mkfifo(FIFO_NAME, 0777);
		if(result != 0){
			perror("mkfifo");
			exit(1);
		}
	}
	printf("\nProducer : %d", getpid());
	pipe_fd = open(FIFO_NAME, O_WRONLY);
	assert(pipe_fd != -1);
	printf("\nPipe : %d", pipe_fd);
	int num = sizeof(buffer) / sizeof(buffer[0]);
	printf(" \n%d", num);
	printf("\nHello");
	write(pipe_fd, &num, sizeof(num));
	result = write(pipe_fd, buffer, sizeof(buffer));
	if(result == -1){
		printf("\nError in pipe");
		exit(1);
	}
	close(pipe_fd);
	printf("\nProducer finished");
	exit(0);
}
