/*************************************************************************
	> File Name: 19.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月21日 星期一 09时43分51秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MC(T, n) (T *)malloc(sizeof(T) * n)
#define CC(T, n) (T *)calloc(n, sizeof(T))

#define init_stack(s, n, T) (__init_stack(s, n, sizeof(T)))
#define push_stack(s, value) ({\
    __typeof(value) __temp = (value);\
    __push_stack(s, (const char *)(&(__temp)));\
})
#define empty_stack(s) (__empty_stack(s))
#define pop_stack(s) (__pop_stack(s))
#define top_stack(s, T) (*((T *)__top_stack(s)))
#define clear_stack(s) (__clear_stack(s))
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}

typedef struct Stack {
    char *data;
    int top, size;
    int value_size;
} Stack;

void __init_stack(Stack *s, int n, int value_size);
void __push_stack(Stack *s, const char *value);
int __empty_stack(Stack *s);
void __pop_stack(Stack *s);
char *__top_stack(Stack *s);
void __clear_stack(Stack *s);


typedef struct Node {
    int flag;
    struct Node *next[26];
} Node;

Node *get_new_node() {
    Node *p = CC(Node, 1);
    return p;
}

int insert(Node *root, char *str) {
    Node *p = root;
    while (str[0]) {
        if (p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = get_new_node();
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return 1;
}

typedef struct Output{
    Node *root;
    int ind, status;
    char *s;
} Output;

void __output(Node *root, int ind, char *s) {
    s[ind] = '\0';
    if (root->flag) {
        printf("%s\n", s);
    }
    //for (int i = 25; i >= 0; --i) {
    //    if (root->next[i] == NULL) continue;
    //    s[ind] = 'a' + i;
        //1 __output(root->next[i], ind + 1, s);
    //}
    //fflush(stdout);
    //2 return ;
}

void output(Node *root, int ind, char *s) {
    Stack *stack = MC(Stack, 1);
    init_stack(stack, 100, Output);
    Output op;
    op.root = root;
    op.ind = ind;
    op.s = s;
    push_stack(stack, op);
    int i = 0;
    while (!empty_stack(stack)) {
        Output *top = &top_stack(stack, Output);
        switch (top->status) {
            case 0:
                __output(root, ind, s);
                top->status = 1;
                break;
            case 1:
                for (i = 0; i < 26; ++i) {
                    if (top->root->next[i] == NULL) {
                        continue;
                    } else {
                        top->s[top->ind] = 'a' + i;
                        op.root = top->root->next[i];
                        op.status = 0;
                        push_stack(stack, top);
                        break;
                    }
                } 
                top->status = 2;
                break;
            case 2:
                pop_stack(stack);
                break;
            default :
                break;
        }
    }
}

void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < 26; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

int main() {
    Node *root = get_new_node();
    int n;
    char str[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        insert(root, str);
    }
    output(root, 0, str);
    fflush(stdout);
    clear(root);
    return 0;
}


void __init_stack(Stack *s, int n, int value_size) {
    s->data = (char *)malloc(value_size * n);
    s->top = -1;
    s->size = n;
    s->value_size = value_size;
    return ;
}

void __push_stack(Stack *s, const char *value) {
    if (s->top == s->size - 1) return ;
    ++(s->top);
    memcpy(s->data + s->top * s->value_size, value, s->value_size);
    return ;
}

int __empty_stack(Stack *s) {
    return s->top == -1;
}

void __pop_stack(Stack *s) {
    if (__empty_stack(s)) return ;
    --(s->top);
    return ;
}

char *__top_stack(Stack *s) {
    if (__empty_stack(s)) return NULL;
    return s->data + s->top * s->value_size;
}

void __clear_stack(Stack *s) {
    free(s->data);
    free(s);
    return ;
}

