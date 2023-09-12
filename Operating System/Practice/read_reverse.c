#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

void main(int argc, char* argv[]){
	assert(argc == 2);
	
	int fd_ip = open(argv[1], O_RDONLY);
	int fd_op = open("read_reverse_op.txt", O_CREAT | O_WRONLY, 0777);
	char c;
	
	long end = lseek(fd_ip, 0, SEEK_END);
	
	while(end > 0){
		end--;
		lseek(fd_ip, end, SEEK_SET);
		read(fd_ip, &c, 1);
		write(fd_op, &c, 1);
	}
	
	close(fd_ip);
	close(fd_op);
}
