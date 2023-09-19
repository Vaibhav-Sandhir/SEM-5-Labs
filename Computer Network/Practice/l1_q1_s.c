#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("10.52.4.94");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);

	int done = 0;	
	while(!done){
		struct sockaddr_in clientaddress;
		int client = sizeof(clientaddress);
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
		
		char decrypted[256];
		char encrypted[256];
		
		recv(new_socket_id, encrypted, sizeof(encrypted), 0);
		printf("\nEncrypted text was %s", encrypted);
		
		for(int i = 0; i < strlen(encrypted); i++){
			decrypted[i] = encrypted[i] - 4;
		}
		
		send(new_socket_id, decrypted, sizeof(decrypted), 0);
		done = 1;
	}	
}
