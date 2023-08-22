#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid = fork();
	int status;
	
	if(pid < 0){
		printf("\nError Occured");
		exit(-1);
	}
	
	else if(pid == 0){
		execl("/home/student/Desktop/210905152_OS/Lab 3/q1", "q1", NULL);
		exit(0);
	}
	else{
		wait(&status);
		printf("\nChild returned %d", status);
	}
}
