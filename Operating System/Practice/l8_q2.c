#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int a;
	int b;
}Input;

void* thread_handler(void* param){
	Input* ip = (Input*)param;
	
	int ans = ip->a + ip->b;
	return ans;
}

void main(){
	Input input;
	Input* ip;
	ip = &input;
	pthread_t thread;
	int ans;
	
	printf("\nEnter first number: ");
	scanf("%d", &ip->a);
	printf("\nEnter second number: ");
	scanf("%d", &ip->b);
	
	pthread_create(&thread, 0, &thread_handler, (void*)ip);
	pthread_join(thread, (void*)&ans);
	
	printf("\nSum is : %d", ans);
}
