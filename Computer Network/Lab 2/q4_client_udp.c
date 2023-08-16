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
	serveraddress.sin_addr.s_addr = inet_addr("10.52.8.115");
	serveraddress.sin_port = htons(PORTNO);	
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	
	while(1){
		char buffer[256] = "Hello form UDP";
		socklen_t server = sizeof(serveraddress);
					if(sendto(socket_id, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddress, server) == -1){
				perror("sendto");
				exit(-1);
			}
	}
	close(socket_id);
	return 0;
}
