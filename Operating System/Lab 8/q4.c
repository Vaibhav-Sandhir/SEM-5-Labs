#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct input{
	int n;
	int array[100];
} input;

void *even_thread(void* param){
	input* ip = (input*)param;
	int sum = 0;
	for(int i = 0; i < ip->n; i++){
		if(ip->array[i] % 2 == 0)
			sum += ip->array[i];
	}
	return sum;
}

void* odd_thread(void* param){
	input* ip = (input*) param;
	int sum = 0;
	for(int i = 0; i < ip-> n; i++){
		if(ip->array[i] % 2 != 0)
			sum += ip->array[i];
	}
	return sum;
}

void main(){
	input ui;
	input* ip = &ui;
	pthread_t t1;
	pthread_t t2;
	printf("\nEnter number of elements: ");
	scanf("%d", &ip->n);
	printf("\nEnter elements");
	for(int i = 0; i < ip->n; i++){
		scanf("%d", &ip->array[i]);
	}
	pthread_create(&t1, 0, &even_thread, (void *)ip);
	pthread_create(&t2, 0, &odd_thread, (void *)ip);
	int res1;
	int res2;
	pthread_join(t1, (void *)&res1);
	pthread_join(t2, (void *)&res2);
	printf("%d", res1 + res2);
}
