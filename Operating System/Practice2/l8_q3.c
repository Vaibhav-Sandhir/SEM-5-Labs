#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int start;
	int end;
}Input;

void* thread_handler(void* param){
	Input* ip = (Input*)param;
	int count = 0;
	int flag = 1;
	int* nums = (int*)malloc(256 * sizeof(int));
	
	for(int i = ip->start; i <= ip->end; i++){
		for(int j = 2; j < i; j++){
			if(i % j == 0){
				flag = 0;
				break;
			}
		}
		if(flag){
			*(nums + count) = i;
			count++;
		}
		flag = 1;
	}
	*(nums + count) = -1;
	
	return (void*)nums;
}

void main(){
	Input input;
	Input* ip = &input;
	
	printf("\nStarting number and ending number: ");
	scanf("%d %d", &ip->start, &ip->end);
	
	pthread_t t1;
	pthread_create(&t1, 0, &thread_handler, (void*)ip);
	int* nums;
	pthread_join(t1, (void**)&nums);
	
	for(int i = 0; *(nums + i) != -1; i++){
		printf("%d  ", *(nums + i));
	}
}
