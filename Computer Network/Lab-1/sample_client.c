#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
	char ch[256];
	char buff[256];
	int socket_id;
	int len;
	int result;
	int n = 1;
	struct sockaddr_in address;
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.20.10.8");
	address.sin_port = htons(10200);
	len = sizeof(address);
	result = connect(socket_id,(struct sockaddr*)&address,len);
	if(result == -1){
		perror("\nCLIENT ERROR");
		exit(1);
	}
	printf("\nEnter String : ");
	scanf("%s", buff);
	ch[strlen(ch)] = '\0';
	write(socket_id,buff,sizeof(buff));
	printf("String Sent Back From Server is ");
	while(n){
		n = read(socket_id,buff,sizeof(buff));
		puts(buff);
	}
}
