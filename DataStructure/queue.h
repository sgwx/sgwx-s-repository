/*************************************************************************
	> File Name: queue.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 08时27分38秒
 ************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

#define ERROR 0
#define OK 1

typedef struct Queue {
    int *data;
    int head, tail, length, count;
}Queue;

void init_queue(Queue *q, int n);
int push_queue(Queue *q, int value);
int pop_queue(Queue *q);
int top_queue(Queue *q);
int empty_queue(Queue *q);
void output_queue(Queue *q);
void clear_queue(Queue *q);

#endif