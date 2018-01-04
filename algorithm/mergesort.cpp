/*************************************************************************
> File Name: mergesort.cpp
> Author: 
> Mail: 
> Created Time: 2017年08月19日 星期六 18时36分59秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define init_stack(s, n, T) (__init_stack(s, n, sizeof(T)))
#define push_stack(s, value) ({\
    __typeof(value) __temp =(value);\
    __push_stack(s,(const char *)(&(__temp)));\
})
#define empty_stack(s) (__empty_stack(s))
#define pop_stack(s) (__pop_stack(s))
#define top_stack(s, T) (*((T *)__top_stack(s)))
#define clear_stack(s) (__clear_stack(s))
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}

#define ERROR 0
#define OK 1

typedef struct Stack {
    char *data;
    int top, size, value_size;
} Statck;

void __init_stack(Stack *s, int n, int value_size);
int __push_stack(Stack *s, const char *value);
int __empty_stack(Stack *s);
int __pop_stack(Stack *s);
char *__top_stack(Stack *s);
void __clear_stack(Stack *s);

void __merge_sort(int *arr, int l, int r, int mid) {
    // if (r <= l) return ;
    //if (r - l == 1) {
    //    if (arr[r] < arr[l]) {
    //        swap(arr[r], arr[l]);
    //    }
    //    return ;
    //}
    //mid = (r + l) / 2;
    //2merge_sort(arr, l, mid, mid);
    //3merge_sort(arr, mid + 1, r, mid);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int ind1 = l, ind2 = mid + 1;
    int k = 0;
    while(ind1 <= mid || ind2 <= r) {
        if (ind1 > mid) {
            temp[k++] = arr[ind2++];
        } else if (ind2 > r) {
            temp[k++] = arr[ind1++];
        } else if (arr[ind1] > arr[ind2]) {
            temp[k++] = arr[ind2++];
        } else {
            temp[k++] = arr[ind1++];
        }
    }
    for (int i = l; i <=r; ++i) {
        arr[i] = temp[i - l];
    }
    free(temp);
    //return ;
}

typedef struct MergeSort {
    int *arr;
    int l, r, mid;
    int status;
} Mergesort;

void init_merge_sort(Mergesort *m, int *arr, int l, int r, int status) {
    m->arr = arr;
    m->l = l;
    m->r = r;
    m->mid = (l + r) / 2;
    m->status = 0;
}

void merge_sort(int *arr, int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    init_stack(s, 23, Mergesort);
    Mergesort m;
    init_merge_sort(&m, arr, 0, n - 1, 0);
    push_stack(s, m);
    while (!empty_stack(s)) {
        Mergesort *tm = &top_stack(s, Mergesort);
        switch (tm->status) {
            case 0:
                if (m.r - m.l == 1) {
                    if (m.arr[tm->r] < m.arr[tm->l]) {
                        swap(m.arr[m.r], m.arr[m.l]);
                    }
                    m.status = 4;
                }
                tm->status = 1;
                break;
            case 1:
                init_merge_sort(&m, arr, tm->l, tm->mid, 0);
                push_stack(s, m);
                tm->status = 2;
                break;
            case 2:
                init_merge_sort(&m, arr, tm->mid + 1, tm->r, 0);
                push_stack(s, m);
                tm->status = 3;
                break;
            case 3:
                __merge_sort(tm->arr, tm->l, tm->r, (tm->l + tm->r) / 2);
                tm->status = 4;
                break;
            case 4:
                pop_stack(s);
                break;
            default :
                break;
        }
    }
    return ;
}

int main() {
    //sleep(3);
    int arr[10] = {9, 2, 5, 6, 7, 3, 4, 8, 1, 10};
    merge_sort(arr, 10);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

void __init_stack(Stack *s, int n, int value_size) {
    s->data = (char *)malloc(value_size * n);
    s->top = -1;
    s->size = n;
    s->value_size = value_size;
    return ;
}

 int __push_stack(Stack *s, const char *value) {
    if (s->top == s->size - 1) {
        return ERROR;
    }
    ++(s->top);
    memcpy(s->data + s->top * s->value_size, value, s->value_size);
    return OK;
}


int __empty_stack(Stack *s) {
    return s->top == -1;
}

int __pop_stack(Stack *s) {
    if (__empty_stack(s)) {
        return ERROR;
    }
    --(s->top);
    return OK;
}

char *__top_stack(Stack *s) {
    if (__empty_stack(s)) {
    return NULL;
    }
    return s->data + s->top * s->value_size;
}

void __clear_stack(Stack *s) {
    free(s->data);
    free(s);
    return ;
}

