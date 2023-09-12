#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main(){
	pid_t pid;
	int status;
	pid = fork();
	
	if(pid < 0){
		perror("fork");
		exit(-1);
	}
	
	else if(pid == 0){
		exit(0);
	}
	
	else{
		sleep(100000);
	}
}
