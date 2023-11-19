// Process A which is sender

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 512      // Max size which can be transferred

// Will send structures from process A to process B

typedef struct Message{
	int number;
	int message_type;
}Message;

int main(){
	Message message;
	int msg_queue_id = msgget((key_t)1234, 0666 | IPC_CREAT);
	// Above creates a message queue and returns its id, (key_t) is for uniquely identifying the message queue so same key should be used across the processes 
	// 0666 is permissions and IPC_CREAT makes the message queue if it does not exist
	
	if(msg_queue_id == -1){
		printf("\nCould not create message queue");
		exit(1);
	}
	
	int running = 1;
	
	while(running){
		printf("\nEnter a number: ");
		scanf("%d", &message.number);
		message.message_type = 1;
		int res = msgsnd(msg_queue_id, (void *)&message, MAX, 0); // Message sending syntax
		if(res == -1){
			printf("\nCould not send message");
		}
		if(message.number == -1){
			running = 0;   // Keep on sending numbers until -1 is entered
		}
	}
}
