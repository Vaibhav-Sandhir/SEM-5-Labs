// Process B which will receiver number and check palindrome

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct Message{
	int number;
	int message_type;
}Message;

int isPalindrome(int num){
	int temp = num;
	int rev = 0;
	int remainder = 0;
	
	while(temp > 0){
		remainder = temp % 10;
		rev = (rev * 10) + remainder;
		temp = temp / 10;
	}
	
	if(rev == num){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	Message message;
	int msg_queue_id = msgget((key_t)1234, 0666 | IPC_CREAT);
	
	if(msg_queue_id == -1){
		printf("\nCould not create message queue");
		exit(1);
	}
	
	int running = 1;
	
	while(running){
		int res = msgrcv(msg_queue_id, (void*)&message, BUFSIZ, 0, 0);
		if(res == -1){
			printf("\nError in receving message");
			exit(1);
		}
		if(message.number == -1){
			running = 0;
			exit(0);
		}
		if(isPalindrome(message.number) == 1){
			printf("\n%d is a palindrome", message.number);
		}
		else{
			printf("\n%d is not a palindrome", message.number);
		}
	}
	
	// Deleteing the message queue
	
	int res = msgctl(msg_queue_id, IPC_RMID, 0);
	if(res == -1){
		printf("\nCould not delete message queue");
	}
}
