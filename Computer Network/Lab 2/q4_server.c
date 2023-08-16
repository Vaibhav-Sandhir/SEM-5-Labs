#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>	
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define PORTNO 10200

int main(){
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int range = 0;
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("10.52.8.115");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(tcp_socket, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	bind(udp_socket, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	
	listen(tcp_socket, 5);
	listen(udp_socket, 5);
	
	fd_set readfds;                 // set of file descriptors
	FD_ZERO(&readfds);              // clearing all file descriptorsd
	FD_SET(tcp_socket, &readfds);   // adding the tcp socket to the set
	FD_SET(udp_socket, &readfds);   // adding the udp socket to the set
	
	if(tcp_socket > udp_socket)
		range = tcp_socket;
	else
		range = udp_socket;
	
	while(1){
		fd_set temp_fds = readfds;
		
		int result = select(range + 1, &temp_fds, NULL, NULL, NULL);
		
		if(result == -1){
			printf("\nError Occured");
			exit(-1);
		}
		
		if(FD_ISSET(udp_socket, &temp_fds)){
			printf("\nHello");
			struct sockaddr_in clientaddress;
			clientaddress.sin_family = AF_INET;
    			clientaddress.sin_addr.s_addr = inet_addr("10.52.8.115"); // Replace with the actual client's IP address
    			clientaddress.sin_port = htons(PORTNO);
    			socklen_t client = sizeof(clientaddress); // Replace with the actual client's port number

			char buffer[256];
			
					ssize_t bytes = recvfrom(udp_socket, buffer, 256, 0, (struct sockaddr*)&clientaddress, &client);
		
		if(bytes == -1){
			perror("revfrom");
			exit(-1);
		}
		
		buffer[bytes] = '\0';
		
		printf("%s", buffer);
		}
		
		if(FD_ISSET(tcp_socket, &temp_fds)){
			struct sockaddr_in clientaddress;
			int client = sizeof(clientaddress);
			int new_socket_id = accept(tcp_socket, (struct sockaddr*)&clientaddress, &client);
			char buffer[256] = "From TCP Hello";
			send(new_socket_id, buffer, sizeof(buffer), 0);	
		}
	}
	
	close(tcp_socket);
	close(udp_socket);
	return 0;		
}
