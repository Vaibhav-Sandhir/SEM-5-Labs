#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int n;
	int arr[256];
}Input;

void* thread_even(void* param){
	Input* ip = (Input*)param;
	int* res1 = (int*)malloc(sizeof(int));
	
	for(int i = 0; i < ip->n; i++){
		if(ip->arr[i] % 2 == 0){
			(*res1) += ip->arr[i];
		}
	}
	
	return (void*)res1;
}

void* thread_odd(void* param){
	Input* ip = (Input*)param;
	int* res2 = (int*)malloc(sizeof(int));
	
	for(int i = 0; i < ip->n; i++){
		if(ip->arr[i] %2 != 0){
			(*res2) += ip->arr[i];
		}
	}
	
	return (void*)res2;
}

void main(){
	Input input;
	Input* ip = &input;
	
	printf("\nEnter number of elements: ");
	scanf("%d", &ip->n);
	printf("\nEnter array elements: ");
	for(int i = 0; i < ip->n; i++){
		scanf("%d", &ip->arr[i]);
	}
	
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, 0, &thread_even, (void*)ip);
	pthread_create(&t2, 0, &thread_odd, (void*)ip);
	int* res1;
	int* res2;
	pthread_join(t1, (void**)&res1);
	pthread_join(t2, (void**)&res2);
	
	printf("\nAnswer is %d", *res1 + *res2);
}
