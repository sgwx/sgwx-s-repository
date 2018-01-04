/*************************************************************************
> File Name: saveAnyTypeData.h
> Author: 
> Mail: 
> Created Time: 2017年08月21日 星期一 14时52分55秒
************************************************************************/

#ifndef _SAVEANYTYPEDATA_H
#define _SAVEANYTYPEDATA_H

#define MC(T, n) ((T *)malloc(sizeof(T) * n))
#define init_stack(s, n, T) (__init_stack(s, n, sizeof(T)))
#define push_stack(s, value) ({ \
    __typeof(value) __temp = (value);\
    __push_stack(s, (const char *)(&(__temp))); \
})
#define empty_stack(s) (__empty_stack(s))
#define pop_stack(s) (__pop_stack(s))
#define top_stack(s, T) (*((T *)__top_stack(s)))
#define clear_stack(s) (__clear_stack(s))

#define ERROR 0
#define OK 1

typedef struct Stack {
    char *data;
    int top, size;
    int value_size;
} Stack;

void __init_stack(Stack *s, int n, int value_size);
int __push_stack(Stack *s, const char *value);
int __empty_stack(Stack *s);
int __pop_stack(Stack *s);
char *__top_stack(Stack *s);
void __clear_stack(Stack *s);

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

#endif
