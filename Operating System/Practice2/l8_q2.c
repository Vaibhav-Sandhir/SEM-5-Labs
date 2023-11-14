#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int n;
	int arr[256];
}Input;

void* thread_handler(void* param){
	Input* ip = (Input*)param;
	int* result = (int*)malloc(sizeof(int));
	
	for(int i = 0; i < ip->n; i++){
		if(ip->arr[i] >= 0){
			(*result) += ip->arr[i];
		}
	}
	
	return (void*)result;
}

void main(){
	Input input;
	Input* ip = &input;
	pthread_t t1;
	
	printf("\nNumber of elements in the array: ");
	scanf("%d", &ip->n);
	printf("\nEnter the elements of the array: ");
	for(int i = 0; i < ip->n; i++){
		scanf("%d", &ip->arr[i]);
	}
	
	int* result;
	
	pthread_create(&t1, 0, &thread_handler, (void*)ip);
	pthread_join(t1, (void**)&result);
	
	printf("\nAnswer is %d", (*result));
}
