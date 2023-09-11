#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int start;
	int end;
}Input;

void* thread_handler(void* param){
	Input* ip = (Input*)param;
	int* sequence = (int*)malloc(256 * sizeof(int));
	int i = 0;
	
	for(int j = ip->start; j <= ip->end; j++){
		int flag = 1;
		for(int k = 2; k < j; k++){
			if(j % k == 0){
				flag = 0;
				break;
			}
		}
		if(flag)
			sequence[i++] = j;	
	}
	sequence[i] = -1;
	
	return sequence;
}

void main(){
	Input input;
	Input* ip;
	ip = &input;
	pthread_t thread;
	
	printf("\nStarting number: ");
	scanf("%d", &ip->start);
	printf("\nEnding number: ");
	scanf("%d", &ip->end);
	
	pthread_create(&thread, 0, &thread_handler, (void*)ip);
	int* sequence;
	pthread_join(thread, (void **)&sequence);
	
	for(int i = 0; sequence[i] != -1; i++){
		printf(" %d", sequence[i]);
	}
	
}
