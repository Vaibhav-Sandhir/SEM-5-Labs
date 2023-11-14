#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int m;
	int n;
	int m1[256][256];
	int m2[256][256];
}Input;

void* thread_handler(void* param){
	Input* ip = (Input*)param;
	int** m3 = (int**)malloc(ip->m * sizeof(int*));
	for(int i = 0; i < ip->m; i++){
		m3[i] = (int*)malloc(ip->n * sizeof(int));
	}
	
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			m3[i][j] = ip->m1[i][j] + ip->m2[i][j]; 
		}
	}
	
	return (void*)m3;
}

void main(){
	Input input;
	Input* ip = &input;
	
	printf("\nEnter rows and columns for both the matrices: ");
	scanf("%d %d", &ip->m, &ip->n);
	printf("\nEnter elements of matrix 1: ");
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			scanf("%d", &ip->m1[i][j]);
		}
	}
	printf("\nEnter elements of matrix 2: ");
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			scanf("%d", &ip->m2[i][j]);
		}
	}
	
	int** m3;
	pthread_t t1;
	pthread_create(&t1, 0, &thread_handler, (void*)ip);
	pthread_join(t1, (void**)&m3);
	
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			printf("%d  ", m3[i][j]);
		}
		printf("\n");
	}
	
}
