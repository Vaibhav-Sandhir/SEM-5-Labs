#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread_handler(void* param){
	int* n = (int*)param;
	int size = *n;
	int* sequence = (int*)malloc(size * sizeof(int));
	for(int i = 0; i < (size); i++){
		if(i == 0 || i == 1){
			*(sequence + i) = i;
		}
		else{
			*(sequence + i) = *(sequence + i - 1) + *(sequence + i - 2);
		}
	}
	return (void*)sequence;	
}

void main(){
	int* n = (int*)malloc(sizeof(int));
	pthread_t t1;
	
	printf("\nHow many fibonacci numbers? ");
	scanf("%d", n);
	
	pthread_create(&t1, 0, &thread_handler, (void*)n);
	int* sequence;
	pthread_join(t1, (void**)&sequence);
	
	for(int i = 0; i < (*n); i++){
		printf("%d  ", *(sequence + i));
	}
}
