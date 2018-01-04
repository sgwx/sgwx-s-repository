#include <stdio.h>
#include "stack.h"

void init_stack(Stack *s, int n) {
    s->data = (char **)malloc(sizeof(char*) * n);
    s->max_size = n;
    s->top_index = -1;    
}

int push_stack(Stack *s, char ch) {
    if (s->top_index >= s->max_size - 1) {
        return ERROR;
    }
    s->top_index++;
    s->data[s->top_index] = strdup(ch);
    return OK;
}

int pop_stack(Stack *s) {
    if (s->top_index == -1) return ERROR;
    s->top_index--;
    return OK;
}

int empty_stack(Stack *s) {
    return s->top_index == -1;
}

char *top_stack(Stack *s) {
    return s->data[s->top_index];
}

void clear(Stack *s) {
    free(s->data);
    free(s);
}







