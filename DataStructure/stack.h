/*************************************************************************
	> File Name: stack.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月06日 星期日 11时06分31秒
 ************************************************************************/

#ifndef _STACK_H
#define _STACK_H

#define ERROR 0
#define oK 1

typedef struct Stack {
    char **data;
    int max_size, top_index;
} Stack;

void init_stack(Stack *s, int n);
int push_stack(Stack *s, char *ch);
int pop_stack(Stack *s);
int empty_stack(Stack *s);
char top_stack(Stack *s);
void clear(Stack *s);

#endif
