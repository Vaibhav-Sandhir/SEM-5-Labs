#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.52.4.94");
	address.sin_port = htons(PORTNO);
	
	int res = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(res == -1){
		perror("\nClient Error");
		exit(0);
	}
	
	double n1;
	char c;
	double n2;
	double ans;
	
	printf("\nEnter first number: ");
	scanf(" %lf", &n1);
	printf("\nEnter operator: ");
	scanf(" %c", &c);
	printf("\nEnter second number: ");
	scanf(" %lf", &n2);
	
	send(socket_id, &n1, sizeof(n1), 0);
	send(socket_id, &c, sizeof(c), 0);
	send(socket_id, &n2, sizeof(n2), 0);
	recv(socket_id, &ans, sizeof(ans), 0);
	
	printf("\nAns: %lf", ans);
}
