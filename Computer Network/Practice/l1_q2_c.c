#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#define PORTNO 10200

int main(){
	while(1){
		int socket_id = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("10.52.4.94");
		address.sin_port = htons(PORTNO);
		
		int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
		
		if(result == -1){
			perror("\nClient Error");
			exit(0);
		}
		
		char buffer[256];
		char ans[256];
		printf("\nEnter string : ");
		scanf(" %[^\n]%*c", buffer);
		
		if(strcmp(buffer, "Stop") == 0)
			exit(0);
		
		send(socket_id, buffer, sizeof(buffer), 0);
		recv(socket_id, ans, sizeof(ans), 0);
		
		printf("\n %s", ans);
		close(socket_id);
	}	
}
