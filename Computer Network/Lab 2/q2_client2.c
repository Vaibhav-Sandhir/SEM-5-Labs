#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.52.3.42");
	address.sin_port = htons(PORTNO);
	
	int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(result == -1){
		perror("\nClient Error");
		exit(0);
	}
	
	double operand1;
	double operand2;
	char operator;
	double answer;
	
	printf("\nEnter first operand: ");
	scanf(" %lf", &operand1);
	printf("\nEnter second operand: ");
	scanf(" %lf", &operand2);
	printf("\nEnter operator: ");
	scanf(" %c", &operator);
	
	send(socket_id, &operand1, sizeof(operand1), 0);
	send(socket_id, &operand2, sizeof(operand2), 0);
	send(socket_id, &operator, sizeof(operator), 0);
	recv(socket_id, &answer, sizeof(answer), 0);
	
	printf("\nResult is : %lf", answer);
	close(socket_id);
}
