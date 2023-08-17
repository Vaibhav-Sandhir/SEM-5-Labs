#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("172.20.10.8");
	serveraddress.sin_port = htons(PORTNO);	
		
	char buffer[256] = "Request from UDP";
	char new[256];
	socklen_t server = sizeof(serveraddress);
	sendto(socket_id, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddress, server);
	recvfrom(socket_id, new, 256, 0, (struct sockaddr*)&serveraddress, &server);
	printf("\n%s", new);
	close(socket_id);
	return 0;
}
