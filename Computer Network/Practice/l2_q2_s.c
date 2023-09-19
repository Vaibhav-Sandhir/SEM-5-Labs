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
			double n1;
			char c;
			double n2;
			double ans;
			recv(new_socket_id, &n1, sizeof(n1), 0);
			recv(new_socket_id, &c, sizeof(c), 0);
			recv(new_socket_id, &n2, sizeof(n2), 0);
			
			if(c == '+')
				ans = n1 + n2;
			else if(c == '-')
				ans = n1 - n2;
			else if(c == '*')
				ans = n1 * n2;
			else if(c == '/')
				ans = n1 / n2;
			
			send(new_socket_id, &ans, sizeof(ans), 0);
			printf("%lf", ans);
			close(new_socket_id);
			exit(0);				
		}
		else{
			wait(NULL);
		}
	}
	close(socket_id);
}
