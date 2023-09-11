#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct input{
	int a;
	int b;
} input;

void* thread_handler(void* param){
	input* nums = (input *)param;
	int result = nums->a + nums->b;
	return (void *)result;
}

void main(){
	input ip;
	input* i = &ip;
	pthread_t thread;
	printf("\nEnter 1st and 2nd number: ");
	scanf("%d %d", &i->a, &i->b);
	pthread_create(&thread, 0, &thread_handler, (void *)i);
	int result;
	pthread_join(thread, (void *)&result);
	printf("\nAnswer is : %d", result);
}
