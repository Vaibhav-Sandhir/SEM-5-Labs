#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(){
	pid_t pid = fork();
	int n = 0;
	char message[256];
	int status;
	
	if(pid < 0){
		printf("\nError Occured");
		exit(-1);
	}
	
	else if(pid == 0){
		n = 3;
		strcpy(message, "I am the child");
	}
	
	else{
		n = 5;
		strcpy(message, "I am the parent");
		wait(&status);
		printf("\nChild returned: %d", status);
	}
	for(; n > 0; n--){
		printf("\n%s", message);
	}
	return 0;
}
