#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("172.20.10.8");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	while(1){
		struct sockaddr_in clientaddress;
		int client = sizeof(clientaddress);
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
		
		int parent_id = fork();
		
		if(parent_id == 0){
			double operand1;
			double operand2;
			char operator;
			double answer;
			
			recv(new_socket_id, &operand1, sizeof(operand1), 0);
			recv(new_socket_id, &operand2, sizeof(operand2), 0);
			recv(new_socket_id, &operator, sizeof(operator), 0);
			
			if(operator == '+')
				answer = operand1 + operand2;
			else if(operator == '-')
				answer = operand1 - operand2;
			else if(operator == '*')
				answer = operand1 * operand2;
			else if(operator == '/')
				answer = operand1 / operand2;
			
			send(new_socket_id, &answer, sizeof(answer), 0);
			printf("%lf", answer);
			close(new_socket_id);
			exit(0);					
		}
		
		else{
			wait(NULL);
		}
	}
	close(socket_id);
}
