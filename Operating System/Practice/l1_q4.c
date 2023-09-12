#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char* argv[]){
	assert(argc == 2);
	char c;
	int fd_ip = open(argv[1], O_RDONLY);
	int fd_op = open("l1_q4_copy.txt", O_CREAT | O_WRONLY, 0777);
	
	while(read(fd_ip, &c, 1) > 0){
		write(fd_op, &c, sizeof(c));
	}
	
	close(fd_ip);
	close(fd_op);
}

