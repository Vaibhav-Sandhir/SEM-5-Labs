#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
volatile int counter = 0;

/*In summary, the use of volatile is a way to ensure that the counter variable is accessed from memory rather than being cached in registers or optimized in a way that might not work correctly in a multi-threaded environment*/


void* thread_handler(void* param){
	char* name = (char*)param;
	printf("\nThread being executed : %s", name);
	for(int i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex);
		counter++;
		printf("\nCount = %d", counter);
		pthread_mutex_unlock(&mutex);	
	}
}

void main(){
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, 0, &thread_handler, "T1");
	pthread_create(&t2, 0, &thread_handler, "T2");
	pthread_join(t1, 0);
	pthread_join(t2, 0);
	pthread_mutex_destroy(&mutex);
	return;
}
