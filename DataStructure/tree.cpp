/*************************************************************************
	> File Name: 9.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 09时03分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "test.h"

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node, *Tree;

Node *init(int data) {
    Node *bt = (Node *)malloc(sizeof(Node));
    bt->data = data;
    bt->lchild = NULL;
    bt->rchild = NULL;
    return bt;
}

Node *insert(Tree bt, int data) {
    if (bt == NULL) {
        bt = init(data);
    }
    if (bt->data > data) {
        bt->lchild = insert(bt->lchild, data);
    } else if (bt->data < data){
        bt->rchild = insert(bt->rchild, data);
    }
    return bt;
}

Node *search(Tree bt, int data) {
    if (bt == NULL || bt->data == data) {
        return bt;
    }
    if (bt->data > data) {
        return search(bt->lchild, data);
    }
    if (bt->data < data) {
        return search(bt->rchild, data);
    }
}

void pre_order(Tree bt) {
    if (bt == NULL) return;
    printf("%d ", bt->data);
    pre_order(bt->lchild);
    pre_order(bt->rchild);
}

void in_order(Tree bt) {
    if (bt == NULL) return;
    in_order(bt->lchild);
    printf("%d ", bt->data);
    in_order(bt->rchild);
}

void post_order(Tree bt) {
    if (bt == NULL) return;
    post_order(bt->lchild);
    post_order(bt->rchild);
    printf("%d ", bt->data);
}

void clear(Tree bt) {
    if (bt == NULL) return;
    clear(bt->lchild);
    clear(bt->rchild);
    free(bt);
}

TEST (Tree, insert_and_search) {
    Tree tree = NULL, p = NULL, q = NULL;
    int n;
    for (int i = 0; i < 5; ++i) {
        scanf("%d", &n);
        p = insert(tree, n);
        ASSERT_EQ(p->data, n);
    }
    clear(p);
    clear(tree);
}

int main() {
    Tree tree = NULL;
    int n, opr;
    while (scanf("%d", &opr) != EOF) {
        switch (opr) {
            case 0:
                scanf("%d", &n);
                tree = insert(tree, n);
                break;
            case 1:
                scanf("%d", &n);
                search(tree, n);
                break;
            case 2:
                printf("pre_order is:\n");
                pre_order(tree);
                break;
        }
    }
    clear(tree);
    return 0;
}

