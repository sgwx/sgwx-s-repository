/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月11日 星期六 14时10分28秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ({ \
    __typeof(a) temp_a = (a); \
    __typeof(b) temp_b = (b); \
    temp_a > temp_b ? temp_a : temp_b; \
})

typedef struct AVLTree {
    int data, height;
    struct AVLTree *lchild, *rchild;
} AVLTree;

AVLTree *init(int data) {
    AVLTree *p = (AVLTree *)malloc(sizeof(AVLTree));
    p->data = data;
    p->height = 1;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

void clear(AVLTree *p) {
    if (p == NULL) return ;
    clear(p->lchild);
    clear(p->rchild);
    free(p);
}

int tree_height(AVLTree *p) {
    if (p == NULL) return 0;
    return p->height;
}

int get_height(AVLTree *p) {
    if (p == NULL) return 0;
    return MAX(tree_height(p->lchild), tree_height(p->rchild)) + 1;
}

AVLTree *left_rotate(AVLTree *p) {
    AVLTree *temp = p->rchild;
    p->rchild = temp->lchild;
    temp->lchild = p;
    temp->height = get_height(temp);
    p->height = get_height(p);
    return temp;
}

AVLTree *right_rotate(AVLTree *p) {
    AVLTree *temp = p->lchild;
    p->lchild = temp->rchild;
    temp->rchild = p;
    p->height = get_height(p);
    temp->height = get_height(temp);
    return temp;
}

int is_balance(AVLTree *p) {
    return abs(tree_height(p->lchild) - tree_height(p->rchild)) <= 1;
}

AVLTree *maintain(AVLTree *p, int flag) {
    p->height = get_height(p);
    if (is_balance(p)) return p;
    if (flag == 0) {
        if (tree_height(p->lchild) < tree_height(p->rchild)) {
            p->lchild = left_rotate(p->lchild);
        }
        p = right_rotate(p);
    } else {
        if (tree_height(p->rchild) < tree_height(p->lchild)) {
            p->rchild = right_rotate(p->rchild);
        }
        p = left_rotate(p);
    }
    return p;
}

AVLTree *predecessor(AVLTree *p) {
    AVLTree *temp = p->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

AVLTree *insert_node(AVLTree *p, int data) {
    if (p == NULL) {
        return init(data);
    } else if (p->data == data) {
        return p;
    } else if (p->data > data) {
        p->lchild = insert_node(p->lchild, data);
    } else {
        p->rchild = insert_node(p->rchild, data);
    }
    p = maintain(p, data > p->data);
    return p;
}

AVLTree *delete_node(AVLTree *p, int data) {
    if (p->data > data) {
        p->lchild = delete_node(p->lchild, data);
        p = maintain(p, 1);
    } else if (p->data < data) {
        p->rchild = delete_node(p->rchild, data);
        p = maintain(p, 0);
    } else {
        if (p->lchild == NULL && p->rchild == NULL) {
            free(p);
            return NULL;
        } else if (p->lchild == NULL || p->rchild == NULL) {
            AVLTree *temp = p->lchild != NULL ? p->lchild : p->rchild;
            free(p);
            return temp;
        } else {
            AVLTree *temp = predecessor(p);
            temp->data ^= p->data;
            p->data ^= temp->data;
            temp->data ^= p->data;
            p->lchild = delete_node(p->lchild, data);
            p = maintain(p, 1);
        }
    }
    return p;
}

void inorder(AVLTree *p) {
    if (p == NULL) return;
    inorder(p->lchild);
    printf("%d(%d,%d)\n", p->data, tree_height(p->lchild), tree_height(p->rchild));
    inorder(p->rchild);
    return ;
}

int main() {
    int opr, n;
    AVLTree *root = NULL;
    while (scanf("%d%d", &opr, &n) != EOF) {
        switch(opr) {
            case 0:
                root = insert_node(root, n);
                break;
            case 1:
                root = delete_node(root, n);
                break;
        }
        printf("Inorder\n");
        inorder(root);
        printf("--------\n");
    }
    clear(root);
    return 0;
}

