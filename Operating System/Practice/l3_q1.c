#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void main(){
	pid_t pid;
	int status;
	
	pid = fork();
	
	if(pid < 0){
		perror("fork");
		exit(-1);
	}
	
	else if(pid == 0){
		for(int i = 0; i < 3; i++){
			printf("\nI am child");
		}
	}
	
	else{
		wait(&status);
		for(int i = 0; i < 2; i++){
			printf("\nI am parent");
		}
	}
	return;
}
