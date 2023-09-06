#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

int main(int argc, char*argv[]){
	int pipe_fd[2];
	pid_t process_id;
	char buf;
	assert(argc == 2);
	int result = pipe(pipe_fd);
	
	if(result == -1){
		perror("pipe");
		exit(1);
	}
	process_id = fork();
	
	if(process_id == -1){
		perror("fork");
		exit(1);
	}
	
	if(process_id == 0){
		close(pipe_fd[1]);
		while(read(pipe_fd[0], &buf, 1) > 0){
			write(1, &buf, 1);
			write(1, "\n", 1);
		}
		close(pipe_fd[0]);
		exit(1);
	}
	else{
		close(pipe_fd[0]);
		write(pipe_fd[1], argv[1], strlen(argv[1]));
		close(pipe_fd[1]);
		wait(NULL);
		exit(1);
	}
}
