#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main(){
	int status;
	pid_t pid = fork();
	
	if(pid < 0){
		printf("\nError Occured");
		exit(-1);
	}
	
	else if(pid == 0){
		printf("\nInside Child process");
		printf("\nCurrent ID: %d", getpid());
		printf("\nParent ID: %d", getppid());
		exit(0);
	}
	
	else{
		wait(&status);
		printf("\nInside Parent process");
		printf("\nCurrent ID: %d", getpid());
		printf("\nParent ID: %d", getppid());
	}
}
