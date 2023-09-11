#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void* thread_handler(void* number){
	int n = (int)number;
	int* primes = (int*)malloc(n * sizeof(int));
	int k = 0;
	for(int i = 2; i <= n; i++){
		int flag = 0;
		for(int j = 2; j <=n && j != i; j++){
			if(i % j == 0){
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			primes[k++] = i;
	}
	return primes;
}

void main(){
	int num = 0;
	printf("\nTill which number? ");
	scanf("%d", &num);
	pthread_t thread;
	pthread_create(&thread, 0, &thread_handler,(void *)num);
	
	int* primes;
	
	pthread_join(thread, (void **)&primes);
	
	for(int i = 0; i < num; i++){
		printf(" %d", *(primes + i));
	}
}
