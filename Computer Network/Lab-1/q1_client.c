#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.20.10.3");
	address.sin_port = htons(10200);
	int result = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	if(result == -1){
		perror("\nClient Error");
		exit(1);
	}
	
	int n = 1;
	char plaintext[256];
	char encrypted[256];
	
	printf("\nEnter Message: ");
	scanf("%s", plaintext);
	
	for(int i = 0; i < strlen(plaintext); i++){
		encrypted[i] = plaintext[i] + 4;
	}
	
	write(socket_id, encrypted, sizeof(encrypted)); 
	  
}
