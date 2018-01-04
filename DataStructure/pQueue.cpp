/*************************************************************************
	> File Name: 12.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 09时59分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

#define ERROR 0
#define OK 1

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}


typedef struct pQueue {
    int *data;
    int size, length;
} pQueue;

int cmp_value(int a, int b) {
    if (a > b) return 1;
    return 0;
}

void init(pQueue *pq, int n) {
    pq->data = (int *)malloc(sizeof(int) * n);
    pq->size = 0;
    pq->length = n;
}

int push(pQueue *pq, int value) {
    if (pq->size >= pq->length) return ERROR;
    pq->data[pq->size] = value;
    int c = pq->size;
    int f = (c - 1) / 2;
    while (cmp_value(pq->data[c], pq->data[f]))  {     
        swap(pq->data[c], pq->data[f]);
        c = f;
        f = (c - 1) / 2;
    }
    pq->size++;
    return OK;
}

void update(pQueue *pq) {
    int l, r, max_index, loc;
    max_index = 0, loc = -1;
    while(max_index != loc) {
        loc = max_index;
        l = loc * 2 + 1;
        r = loc * 2 + 2;
        if (l < loc && pq->data[l] > pq->data[max_index]) {
            max_index = l;
        }
        if (r < loc && pq->data[r] > pq->data[max_index]) {
            max_index = r;
        }
        if (max_index != loc) {
            swap(pq->data[max_index], pq->data[loc]);
        }
    }

}

int empty(pQueue *pq) {
    return pq->size == 0;
}

int pop(pQueue *pq) {
    if (empty(pq)) {
        return ERROR;
    }
    swap(pq->data[pq->size - 1], pq->data[0]);
    pq->size--;
    update(pq);
    return OK;
}

int front(pQueue *pq) {
    return pq->data[0];
}

void clear(pQueue *pq) {
    free(pq->data);
    free(pq);
}

TEST (push_and_pop, test) {
    int n, a, k;
    scanf("%d", &n);
    pQueue *pq = (pQueue *)malloc(sizeof(pQueue));
    init(pq, n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a);
        k = push(pq, a);
        ASSERT_EQ(k, OK);
    }
    while (!empty(pq)) {
        k = pop(pq);
        ASSERT_EQ(k, OK);
    }
    clear(pq);
}

int main() {
    /*int n, a;
    scanf("%d", &n);
    pQueue *pq = (pQueue *)malloc(sizeof(pQueue));
    init(pq, n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        push(pq, a);
    }
    while (!empty(pq)) {
        printf("%d", front(pq));
        pop(pq);
    }
    clear(pq);*/
    return 0;
}



