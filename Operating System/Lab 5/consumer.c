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
	int result;
	int buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;
	int num;
	printf("Consumer : %d", getpid());
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	assert(pipe_fd != -1);
	read(pipe_fd, &num, sizeof(num));
	printf("\n%d\n", num);
	printf("Hello");
	int data[num];
	read(pipe_fd, data, sizeof(data));
	for(int i = 0; i < num; i++){
		printf(" %d", data[i]);
	}
	close(pipe_fd);
	printf("\nConsumer finished");
	exit(0);	
}
