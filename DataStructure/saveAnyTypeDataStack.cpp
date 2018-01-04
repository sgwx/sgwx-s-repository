/*************************************************************************
	> File Name: 18.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月18日 星期五 08时15分52秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define init_stack(s, n, T) (__init_stack(s, n, sizeof(T)))
#define push_stack(s, value) ({ \
    __typeof(value) __temp = (value);\
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

#define MC(T, n) (T *)malloc(sizeof(T) * n)

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

typedef struct Node {
    int val;
    struct Node *lchild, *rchild;
} Node;

typedef struct PreorderArgs {
    Node *root;
    int status;//从0开始  当前运行到第几个代码段
} PreorderArgs;

int __preorder(Node *root) {
    //if (root == NULL) return 1;//边界条件编号为0
    printf("%d ", root->val);//编号为1
    //root->lchild && preorder(root->lchild);//编号为2
    //root->rchild && preorder(root->rchild);//3
    return 1;//4
}

int preorder(Node *root) {
    Stack *s = (Stack *s)malloc(sizeof(Stack));
    init_stack(s, 1000, PreorderArgs);
    PreorderArgs pa;
    pa.root = root;
    pa.status = 0;
    push_stack(s, pa);
    while (!empty_stack(s)) {
        PreorderArgs *tpa = &top_stack(s, PreorderArgs);
        switch (tpa.status) {
            case 0:
                if (tpa->root == NULL) {
                    tpa->status = 4;
                } else {
                    tpa->status = 1;
                }
                break;
            case 1:
                __preorder(tpa->root);
                tpa->status = 2;
                break;
            case 2:
                if (tpa->root->lchild) {
                    pa.root = tpa->root->lchild;
                    pa.status = 0;
                    push_stack(s, pa);
                }
                tpa->status = 3;
                break;
            case 3:
                if (tpa->root->rchild) {
                    pa.root = tpa->root->rchild;
                    tpa->status = 0;
                    push_stack(s);
                }
                tpa->status = 4;
                break;
            case 4:
                pop_stack(s);
                break;
            default :
                printf("ERROR\n");
                break;
        }
    }
    return 1;
}

typedef struct Node {
    int val;
    struct Node *lchild, *rchild;
} Node;

typedef struct Postorder {
    Node *root;
    int status;
} Postorder;

void __postorder(Node *root) {
    //0 :if (root == NULL) return ;
    //1 :root->lchild && __postorder(root->lchild);
    //2 :root->rchild && __postorder(root->rchild);
    printf("%d ", root->val);
    //4 :return ;
}

Node *init(int val) {
    Node *p = MC(Node, 1);
    p->val = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *build(char *str) {
    Node *p = NULL, *last_p = NULL;
    Stack *stack = MC(Stack, 1);
    init_stack(stack, strlen(str), Node *);
    int k = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(' :                   
                k = 0;               
                push_stack(stack, p);
                p = NULL;
                break;               
            case ')' :
                last_p = top_stack(stack, Node *);
                pop_stack(stack);
                break;
            case ',' :
                k = 1;
                p = NULL;
                break;
            case ' ':
                break;
            default :
                p = init(str[0] - '0');
                if (!empty_stack(stack) && k == 0) {                
                    top_stack(stack, Node *)->lchild = p;       
                } else if (!empty_stack(stack) && k == 1) {
                    top_stack(stack, Node *)->rchild = p;                   
                }
                break;            
        }
        ++str;               
    }
    if (p && !last_p) last_p = p;
    clear_stack(stack);
    return last_p;
}

void postorder(Node *root) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    init_stack(s, 1000, Postorder);
    Postorder poa;
    poa.root = root;
    poa.status = 0;
    push_stack(s, poa);
    while (!empty_stack(s)) {
        Postorder *pa = &top_stack(s, Postorder);
        switch (pa->status) {
            case 0:
                if (poa.root == NULL) {
                    poa.status = 4;
                } else {
                    poa.status = 1;
                }
                break;
            case 1:
                if (pa->root->lchild) {
                    pa->root = pa->root->lchild;
                    push_stack(s, pa);
                    poa.status = 0;
                } else {
                    poa.status = 2;
                }    
                break;
            case 2:
                if (pa->root->rchild) {
                    pa->root = pa->root->rchild;
                    push_stack(s, pa);
                    poa.status = 0;
                } else {
                    poa.status = 2;
                }    
                break;
            case 3:
                __postorder(poa.root);
                pa->status = 4;
                break;
            case 4:
                pop_stack(s);
                break;
            default :
                printf("ERROR");
                break;
        }    
    }
    return ;
}

int main() {
    char s[] = "1(3(4(8,9),7),6)";
    Node *root = build(s);
    postorder(root);
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
    if (s->top == s->size - 1) return ERROR;
    s->top++;
    memcpy(s->data + s->top * s->value_size, value, s->value_size);
    return OK;
}

int __empty_stack(Stack *s) {
    return s->top == -1;
}

int __pop_stack(Stack *s) {
    if (empty_stack(s)) return ERROR;
    --(s->top);
    return OK;
}

char *__top_stack(Stack *s) {
    if (__empty_stack(s)) return NULL;
    return s->data + s->top * s->value_size;
}

void __clear_stack(Stack *s) {
    free(s->data);
    free(s);
}

