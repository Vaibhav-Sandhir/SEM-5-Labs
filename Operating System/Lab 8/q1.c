#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_handler(void* number){
	int n = (int)number;
	int* sequence = (int*)malloc(n * sizeof(int));
	for(int i = 0; i < n; i++){
		if(i == 0 || i == 1){
			sequence[i] = i;
		}
		else{
			sequence[i] = sequence[i - 1] + sequence[i - 2];
		}
	}
	
	return (void*)sequence;
}

void main(){
	int num = 0;
	printf("\nHow many fibonacci numbers? ");
	scanf("%d", &num);
	pthread_t thread;
	pthread_create(&thread, 0, &thread_handler,(void *)num);
	
	int* sequence;
	
	pthread_join(thread, (void **)&sequence);
	
	for(int i = 0; i < num; i++){
		printf(" %d", *(sequence + i));
	}
}
