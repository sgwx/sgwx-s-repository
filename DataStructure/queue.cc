#include"queue.h"
#include<stdlib.h>
#include<stdio.h>


void init_queue(Queue *q, int n) {
    q->data = (int *)malloc(sizeof(int) * n);
    q->count = 0;
    q->length = n;
    q->head = 0;
    q->tail = -1;
}

int push_queue(Queue *q, int value) {
    if (q->count == q->length) {
        return ERROR;
    }
    q->tail = (q->tail + 1) % q->length;
    q->data[q->tail] = value;
    q->count++;
    return OK;
}

int pop_queue(Queue *q) {
    if (empty_queue(q)) {
        return ERROR;
    }
    q->head = (q->head + 1) % q->length;
    q->count--;
    return OK;
}

int top_queue(Queue *q) {
    return q->data[q->head];
}

int empty_queue(Queue *q) {
    return q->count == 0;
}

void output_queue(Queue *q) {
    printf("Queue:");
    int index;
    for (int i = 0; i < q->count; i++) {
        index = (q->head + i) % q->length;
        printf("%d ", q->data[index]);
    }
    printf("\n");
}

void clear_queue(Queue *q) {
    free(q->data);
    free(q);
}