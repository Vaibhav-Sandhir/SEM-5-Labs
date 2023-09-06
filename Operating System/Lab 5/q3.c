#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 3

typedef struct Queue {
    int front;
    int rear;
    char* items[size];
} Queue;

int isFull(Queue* q) {
    return ((q->rear + 1) % size) == q->front;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, char str[]) {
    if (isFull(q)) {
        printf("\nQueue is full. Cannot enqueue %s ", str);
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    else {
        q->rear = (q->rear + 1) % size;
    }

    q->items[q->rear] = str;
    printf("\nProcess %s queued", q->items[q->rear]);
}

void dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("\nQueue is empty.");
        return;
    }

    printf("\nProcess %s completed", q->items[q->front]);
    
    if (q->front == q->rear) {
        // If there's only one element, reset the queue
        q->front = -1;
        q->rear = -1;
    }
    else {
        q->front = (q->front + 1) % size;
    }
}

int main() {
    Queue queue;
    Queue* q = &queue;
    q->front = -1;
    q->rear = -1;
    enqueue(q, "P1");
    enqueue(q, "P2");
    enqueue(q, "P3");
    dequeue(q);
    enqueue(q, "P4");
    return 0;
}

