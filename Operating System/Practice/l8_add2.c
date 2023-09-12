#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input{
	int m;
	int n;
	int matrix[256][256];
}Input;

void* row_thread(void* param){
	Input* ip = (Input*)param;
	int sum = 0;
	
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			sum += ip->matrix[i][j];
		}
		printf("Sum of row %d is %d\n", i, sum);
		sum = 0;
	} 	
}

void* column_thread(void* param){
	Input* ip = (Input*)param;
	int sum = 0;
	
	for(int j = 0; j < ip->n; j++){
		for(int i = 0; i < ip->m; i++){
			sum += ip->matrix[i][j];	
		}
		printf("Sum of column %d is %d\n", j, sum);
		sum = 0;
	}
}

void main(){
	Input input;
	Input* ip = &input;
	printf("\nEnter dimensions of the matrix: ");
	scanf("%d %d", &ip-> m, &ip->n);
	printf("\nEnter matrix elements: ");
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			scanf("%d", &ip->matrix[i][j]);
		}
	}
	printf("\n");
	for(int i = 0; i < ip->m; i++){
		for(int j = 0; j < ip->n; j++){
			printf("  %d", ip->matrix[i][j]);
		}
		printf("\n");
	}
	
	pthread_t t1;
	pthread_t t2;
	
	pthread_create(&t1, 0, &row_thread, (void*)ip);
	pthread_create(&t2, 0, &column_thread, (void *)ip);
	
	pthread_join(t1, 0);
	pthread_join(t2, 0);
}
