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
		execl("/home/kali/Desktop/SEM-5-Labs/Operating System/Practice/l3_q1", "l3_q1", NULL);
		printf("\nChild finished");
	}
	
	else{
		wait(&status);
		printf("\nParent finished");
	}
	
	return;
}
