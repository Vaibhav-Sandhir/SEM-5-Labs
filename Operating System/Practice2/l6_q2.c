#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

typedef struct Message{
	char alphabet;
}Message;

int main(){
	void* shared_memory = (void*)0;  // Before attaching the shared_memory pointer to actual memory we just initialize it to 0
	Message *message;
	pid_t pid;
	int status;
	int shared_mem_id = shmget((key_t)1234, sizeof(Message), 0666 | IPC_CREAT);  // Shared memory's identifier
	if(shared_mem_id == -1){
		printf("\nCould not make shared memory");
		exit(0);
	}
	shared_memory = shmat(shared_mem_id, (void*)0, 0); // Attach the shared_memory pointer
	
	printf("\nMemory attached at %p", shared_memory);
	message = (Message*)shared_memory;
	// Establishes a connection between the pointer message and the shared memory segment. It allows you to access and manipulate the shared memory as if it were an instance of 
	// the structure Message
	printf("\nEnter an alphabet: ");
	scanf("%c", &message->alphabet);
	pid = fork();
	
	if(pid == 0){
		char alphabet = message->alphabet;
		
		if(alphabet == 'z'){
			alphabet = 'a';
		}
		else if(alphabet == 'Z'){
			alphabet = 'a';
		}
		else{
			alphabet = (char)((int)alphabet + 1);
		}
		
		message->alphabet = alphabet;
		printf("\nChild update shared memory");
	}
	else{
		wait(NULL);
		printf("\nInside parent process");
		printf("Alphabet in shared memory: %c\n", message->alphabet);
	}
}
