#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 3

typedef struct Queue{
	int items[size];
	int front;
	int rear;
}Queue;

int isEmpty(Queue *q){
	return q->front == -1;
}

int isFull(Queue *q){
	return q->front == (q->rear + 1) % size;
}

void enqueue(Queue *q, int item){
	if(isFull(q)){
		printf("\nQueue is full");
		return;
	}
	
	if(isEmpty(q)){
		q->front = 0;
		q->rear = 0;
	}
	else{
		q->rear = (q->rear + 1) % size;
	}
	
	q->items[q->rear] = item;
}

void dequeue(Queue *q){
	if(isEmpty(q)){
		printf("\nQueue is empty");
		return;
	}
	printf("\n Item %d dequeued", q->items[q->front]);
	
	if(q->front == q->rear){
		q->front = -1;
		q->rear = -1;
	}
	else{
		q->front = (q->front + 1) % size;
	}
}

int isPresent(Queue *q, int item){
    if (isEmpty(q)) {
        printf("\nQueue is empty");
        return 0;
    } 
    else {
        int i = q->front;
        do {
            if(q->items[i] == item){
            	return 1;
            }
            i = (i + 1) % size;
        } while (i != (q->rear + 1) % size);
    }
    return 0;
}

void display(Queue *q) {
    printf("\n------------");
    if (isEmpty(q)) {
        printf("\nQueue is empty");
    } 
    else {
        int i = q->front;
        do {
            printf("\n%d", q->items[i]);
            i = (i + 1) % size;
        } while (i != (q->rear + 1) % size);
    }
    printf("\n------------");
}

void fifo(Queue* q, int n, int reference_string[n]){
	for(int i = 0; i < n; i++){
		int item = reference_string[i];
		if(isPresent(q, item)){
			printf("\nPage hit for page %d", item);
		}
		else{
			if(isFull(q)){
				dequeue(q);
				enqueue(q, item);
			}
			else{
				enqueue(q, item);
			}
			display(q);
		}
	}
}

void main(){
	Queue queue;
	Queue* q = &queue;
	q->front = -1;
	q->rear = -1;
	for(int i = 0; i < 3; i++){
		q->items[i] = -1;
	}
	int n = 20;
	int reference_string[20] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	fifo(q, n, reference_string);
}
