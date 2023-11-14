#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define size 10

typedef struct Process{
	char name[256];
	int burst_time;
}Process;

typedef struct Queue{
	Process items[size];
	int front;
	int rear;
}Queue;

int timer = 0;

int isEmpty(Queue* q){
	return q->front == -1;
}

int isFull(Queue *q){
	return q->front == (q->rear + 1) % size; 
}

void enqueue(Queue *q, Process proc){
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
	q->items[q->rear] = proc;
}

void dequeue(Queue* q){
	if(isEmpty(q)){
		printf("\nQueue is empty");
		return;
	}
	if(q->front == q->rear){
		q->front = -1;
		q->rear = -1;
	}
	else{
		q->front = (q->front + 1) % size;
	}
}

Process peek(Queue* q){
	return q->items[q->front];
}

void initializeProcess(int n, Process list[]){
	 strcpy(list[0].name, "P0");
	 strcpy(list[1].name, "P1");
	 strcpy(list[2].name, "P2");
	 strcpy(list[3].name, "P3");
	 list[0].burst_time = 20; 
	 list[1].burst_time = 10;
	 list[2].burst_time = 30;
	 list[3].burst_time = 50;
}

void status(Queue* q){
	Process temp = peek(q);
	printf("\nProcess %s ran from time %d to %d", temp.name, timer, timer + temp.burst_time - 1);
	timer += temp.burst_time;
}

void fcfs(Queue* q, int n, Process list[n]){
	for(int i = 0; i < n; i++){
		enqueue(q, list[i]);
		status(q);
		dequeue(q);
	}
}

void main(){
	int n = 4;
	Process list[n];
	Queue queue;
	Queue* q = &queue;
	q->front = -1;
	q->rear = -1;
	initializeProcess(n, list);
	fcfs(q, n, list);
}
