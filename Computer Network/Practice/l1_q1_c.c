#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORTNO 10200

int main(){
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
	
	char encrypted[256];
	char decrypted[256];
	char ans[256];
	printf("\nEnter string to be encrypted: ");
	scanf("%s", decrypted);
	for(int i = 0; i < strlen(decrypted); i++){
		encrypted[i] = decrypted[i] + 4;
	}
	send(socket_id, encrypted, sizeof(encrypted), 0);
	recv(socket_id, ans, sizeof(ans), 0);
	
	printf("\nOrignal text was %s", ans);
}
