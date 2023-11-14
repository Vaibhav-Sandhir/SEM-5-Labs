#include <stdio.h>
#include <stdlib.h>
#define size 5

typedef struct Queue{
	int items[size];
	int front;
	int rear;
}Queue;

int isFull(Queue *q){
	return (((q->rear + 1) % size) == q->front);
}

int isEmpty(Queue *q){
	return q->front == -1;
}

void enqueue(Queue *q, int item){
	if(isFull(q)){
		printf("\nQueue is Full");
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
	printf("\nEnqueued %d", item);
	return;
}

void dequeue(Queue *q){
	if(isEmpty(q)){
		printf("\nQueue is Empty");
		return;
	}
	
	printf("\nDequed %d", q->items[q->front]);
	
	if(q->front == q->rear){
		q->front = -1;
		q->rear = -1;
	}
	
	else{
		q->front = (q->front + 1) % size;
	}
	return;
}

void main(){
    Queue queue;
    Queue* q = &queue;
    q->front = -1;
    q->rear = -1;
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    dequeue(q);
    enqueue(q, 4);
}
