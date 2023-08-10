#include <stdio.h>
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
	serveraddress.sin_addr.s_addr = inet_addr("172.20.10.3");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	int done = 0;
	while(!done){
		char encrypted[256];
		char plaintext[256];
		int client;
		struct sockaddr_in clientaddress;
		int n = 1;
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
		client = sizeof(client);
		
		n = read(new_socket_id, encrypted, sizeof(encrypted));
		for(int i = 0; i < strlen(encrypted); i++){
			plaintext[i] = encrypted[i] - 4;
		}
		printf("\nEncrypted Message: %s", encrypted);
		printf("\nOrignal Message: %s", plaintext);
		done = 1;
	}
}

