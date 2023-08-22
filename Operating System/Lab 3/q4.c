//To see the defunct process after cc -o q4 q4.c execute ./q4 & and then execute ps


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int status;
	pid_t pid = fork();
	
	if(pid < 0){
		printf("\nError Occured");
		exit(-1);
	}
	
	else if(pid == 0){
		exit(0);
	}
	else{
		sleep(10000);
	}
	return 0;
}
