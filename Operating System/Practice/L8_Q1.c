#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_handler(void* param){
	int n = (int)param;
	int* sequence = (int*)malloc(n * sizeof(int));
	
	for(int i = 0; i < n; i++){
		if(i == 0 || i == 1)
			sequence[i] = i;
		else
			sequence[i] = sequence[i - 1] + sequence[i - 2];			
	}
	
	return (void*)sequence;
}

void main(){
	int n;
	pthread_t thread;
	printf("\nEnter number of fibonacci numbers: ");
	scanf("%d", &n);
	
	pthread_create(&thread, 0, &thread_handler, (void*)n);
	
	int* sequence;
	
	pthread_join(thread, (void **)&sequence);
	
	for(int i = 0; i < n; i++){
		printf(" %d", sequence[i]);
	}
}
