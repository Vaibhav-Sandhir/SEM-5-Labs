#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <string.h>
#define PORTNO 10200

int isPresent(char word[], char unique[][256], int ind){
	for(int i = 0; i < ind; i++){
		if(strcmp(word, unique[i]) == 0)
			return 1;
	}
	return 0;
}

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("10.52.4.94");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	while(1){
		struct sockaddr_in clientaddress;
		int client = sizeof(clientaddress);
		int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
			
		char buffer[256];
		char unique[256][256];
		char ans[256];
		int ind = 0;
		recv(new_socket_id, buffer, sizeof(buffer), 0);
		
		char* word = strtok(buffer, " \t\n");
		
		while(word != NULL){
			if(!isPresent(word, unique, ind))
				strcpy(unique[ind++], word);		
			word = strtok(NULL, " \t\n");
		}
		for(int i = 0; i < ind; i++){
			printf("%s", unique[i]);
		}
		for(int i = 0; i < ind; i++){
			strcat(ans, unique[i]);
			strcat(ans, " ");
		}
		send(new_socket_id, ans, sizeof(ans), 0);
		strcpy(ans, "");
		strcpy(unique[0], "");
		close(new_socket_id);
	}
}

