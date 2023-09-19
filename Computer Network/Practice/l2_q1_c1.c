#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORTNO 10200

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("10.52.4.94");
	address.sin_port = htons(PORTNO);
	
	int res = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
	if(res == -1){
		perror("\nClient Error");
		exit(0);
	}
	
	int n;
	printf("\nEnter size of array: ");
	scanf("%d", &n);
	int arr[n];
	int ans[n];
	printf("\nEnter array elements");
	for(int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	send(socket_id, &n, sizeof(n), 0);
	send(socket_id, arr, sizeof(arr), 0);
	recv(socket_id, ans, sizeof(ans), 0);
	printf("\nSorted array is:\n");
	for(int i = 0; i < n; i++){
		printf(" %d", ans[i]);
	}
	
}
