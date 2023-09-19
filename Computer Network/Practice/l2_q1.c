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

void sortArray(int arr[], int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			if(arr[j] > arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
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
		int pid = fork();
		if(pid == 0){
			int arr[256];
			int n;
			recv(new_socket_id, &n, sizeof(n), 0);
			recv(new_socket_id, arr, sizeof(arr), 0);
			sortArray(arr, n);
			send(new_socket_id, arr, sizeof(arr), 0);
		}
		else{
			wait(NULL);
		}
	}
}
