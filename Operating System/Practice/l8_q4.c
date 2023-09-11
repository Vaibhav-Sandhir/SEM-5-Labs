#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int n;
	int arr[100];
}Input;

void* thread_even(void* param){
	Input* ip = (Input*)param;
	int* sum = (int*)malloc(sizeof(int));
	
	for(int i = 0; i < ip->n; i++){
		if(ip->arr[i] % 2 == 0)
			*sum += ip->arr[i];
	}
	
	return sum;
}

void* thread_odd(void* param){
	Input* ip = (Input*)param;
	int* sum = (int*)malloc(sizeof(int));
	
	for(int i = 0; i < ip->n; i++){
		if(ip->arr[i] % 2 != 0)
			*sum += ip->arr[i];
	}
	
	return sum;
}

void main(){
	Input input;
	Input* ip;
	ip = &input;
	printf("\nEnter number of elements: ");
	scanf("%d", &ip->n);
	printf("\nEnter elements of the array: ");
	for(int i = 0; i < ip->n; i++){
		scanf("%d", &ip->arr[i]);
	}
	pthread_t t1;
	pthread_t t2;
	
	pthread_create(&t1, 0, &thread_even, (void *)ip);
	pthread_create(&t2, 0, &thread_odd, (void*)ip);
	
	int* res1;
	int* res2;
	
	pthread_join(t1, (void**)&res1);
	pthread_join(t2, (void**)&res2);	
	printf("\nSum of array is : %d", *res1 + *res2);
}
