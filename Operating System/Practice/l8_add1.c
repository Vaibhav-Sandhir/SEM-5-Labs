#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Input {
    int m;
    int n;
    int p;
    int q;
    int m1[256][256];
    int m2[256][256];
} Input;

typedef struct Output {
    int m;
    int n;
    int m3[256][256];
} Output;

void* thread_handler(void* param) {
    Output* op = (Output*)malloc(sizeof(Output));
    Input* ip = (Input*)param;
    op->m = ip->m;
    op->n = ip->n;

    for (int i = 0; i < ip->m; i++) {
        for (int j = 0; j < ip->q; j++) {
            op->m3[i][j] = 0;
            for (int k = 0; k < ip->p; k++) {
                op->m3[i][j] += ip->m1[i][k] * ip->m2[k][j];
            }
        }
    }
    return op;
}

void main() {
    Input input;
    Input* ip = &input;

    printf("\nEnter dimensions of the matrix 1: ");
    scanf("%d %d", &ip->m, &ip->n);
    printf("\nEnter elements of the matrix 1: ");
    for (int i = 0; i < ip->m; i++) {
        for (int j = 0; j < ip->n; j++) {
            scanf("%d", &ip->m1[i][j]);
        }
    }

    printf("\nEnter dimensions of the matrix 2: ");
    scanf("%d %d", &ip->p, &ip->q);
    printf("\nEnter elements of the matrix 2: ");
    for (int i = 0; i < ip->p; i++) {
        for (int j = 0; j < ip->q; j++) {
            scanf("%d", &ip->m2[i][j]);
        }
    }
			
    Output* op;
    pthread_t thread;
    pthread_create(&thread, NULL, &thread_handler, (void*)ip);

    pthread_join(thread, (void**)&op);

    printf("\n");
    for (int i = 0; i < op->m; i++) {
        for (int j = 0; j < op->n; j++) {
            printf("  %d", op->m3[i][j]);
        }
        printf("\n");
    }
}

