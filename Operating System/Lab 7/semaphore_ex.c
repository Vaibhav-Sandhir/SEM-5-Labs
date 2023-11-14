#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
int limit = 3;
int curr;

void* func1(void* param){
	sem_wait(&semaphore); // Decrements the semaphore
	printf("\nThread 1");
}

void* func2(void* param){
	printf("\nThread 2");
	sem_post(&semaphore); // Basically Signal increments the semaphore
}

int main(){
	pthread_t t[2];
	
	sem_init(&semaphore, 0, 0);  // 0 represnts semaphore is shares b/w threads in one process
	pthread_create(&t[0], 0, &func1, 0);
	pthread_create(&t[1], 0, &func2, 0);
	pthread_join(t[1], 0);
	pthread_join(t[0], 0);
	sem_destroy(&semaphore);
}
