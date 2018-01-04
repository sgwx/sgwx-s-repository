/*************************************************************************
	> File Name: 11.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 15时02分54秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

typedef struct RBTNode {
    int key, black;
    struct RBTNode *lchild, *rchild, *father;
} RBTNode;

RBTNode *NIL;

void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->father = NULL;
    NIL->lchild = NIL->rchild = NIL;
    NIL->key = 0;
    NIL->black = 1;
}

RBTNode *init_node(int key) {
    RBTNode *node = (RBTNode *)malloc(sizeof(RBTNode));
    node->father = NULL;
    node->lchild = node->rchild = NIL;
    node->key = key;
    node->black = 0;
    return node;
}

RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild->father = node;
    temp->father = node->father;
    temp->lchild = node;
    node->father = temp;
    return temp;
}

RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild->father = node;
    temp->father = node->father;
    temp->rchild = node;
    node->father = temp;
    return temp;
}

RBTNode *predecessor(RBTNode *node) {
    RBTNode *temp = node->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

int has_red_child(RBTNode *node) {
    return node->lchild->black == 0 || node->rchild->black == 0;
}

RBTNode *insert_maintain(RBTNode *node) {
    if (node->black == 0) return node;
    if (node->lchild->black && node->rchild->black) return node;
    if (!has_red_child(node->lchild) && !has_red_child(node->rchild)) return node;
    if (node->lchild->black == 0 && node->rchild->black == 0) {
        node->black = 0;
        node->lchild->black = node->rchild->black = 1;
        return node;
    } else if (node->lchild->black == 0 && node->lchild->lchild->black == 0) {
        node = right_rotate(node);
        node->lchild->black = node->rchild->black = 1;
        node->black = 0;
    } else if (node->lchild->black == 0 && node->lchild->rchild->black == 0) {
        node->lchild = left_rotate(node->lchild);
        node = right_rotate(node);
        node->lchild->black = node->rchild->black = 1;
        node->black = 0;
    } else if (node->rchild->black == 0 && node->rchild->rchild->black == 0) {
        node = left_rotate(node);
        node->black = 0;
        node->lchild->black = node->rchild->black = 1;
    } else if (node->rchild->black == 0 && node->rchild->lchild->black == 0) {
        node->rchild = right_rotate(node);
        node = left_rotate(node);
        node->lchild->black = node->rchild->black = 1;
        node->black = 0;
    }
    return node;
}

RBTNode *insert_node(RBTNode *node, int key) {
    if (node == NULL || node == NIL) {
        RBTNode *temp = init_node(key);
        temp->black = (node == NULL);
        return temp;
    }
    if (node->key == key) return node;
    if (node->key < key) {
        node->rchild = insert_node(node->rchild, key);
        node->rchild->father = node;
        node = insert_maintain(node);
    } else {
        node->lchild = insert_node(node->lchild, key);
        node->lchild->father = node;
        node = insert_maintain(node);
    } 
    if (node->father == NULL) {
        node->black = 1;
    }
    return node;
}

RBTNode *erase_maintain(RBTNode *node) {
    if (node->lchild->black != 2 && node->rchild->black != 2) return node;
    if (node->lchild->black == 2 && node->rchild->black == 0) {
        node = left_rotate(node);
        node->black = 1;
        node->lchild->black = 0;
        node->lchild = erase_maintain(node->lchild);
    } else if (node->lchild->black == 0 && node->rchild->black == 2) {
        node = right_rotate(node);
        node->black = 1;
        node->rchild->black = 0;
        node->rchild = erase_maintain(node->rchild);
    } else if (node->lchild->black == 2 && node->rchild->black == 1) {
        if (!has_red_child(node->rchild)) {
            node->black++;
            node->lchild->black = 1;
            node->rchild->black = 0;
            return node;
        } else if (node->rchild->rchild->black != 0) {
            node->rchild = right_rotate(node->rchild);
            node->rchild->black = 1;
            node->rchild->rchild->black = 0;
        }
        node = left_rotate(node);
        node->black = node->lchild->black;
        node->lchild->black = node->rchild->black = 1;
        node->lchild->lchild->black = 1;
    } else if (node->lchild->black == 1 && node->rchild->black == 2) {
        if (!has_red_child(node->lchild)) {
            node->black++;
            node->rchild->black = 1;
            node->lchild->black = 0;
            return node;
        } else if (node->lchild->lchild->black != 0) {
            node->lchild = left_rotate(node->lchild);
            node->lchild->black = 1;
            node->lchild->lchild->black = 0;
        }
        node = right_rotate(node);
        node->black = node->rchild->black;
        node->lchild->black = node->rchild->black = 1;
        node->rchild->rchild->black = 1;
    }
    return node;
}

RBTNode *erase_node(RBTNode *node, int key) {
    if (node == NULL || node == NIL) return node;
    if (node->key > key) {
        node->lchild = erase_node(node->lchild, key);
        node = erase_maintain(node);
    } else if (node->key < key) {
        node->rchild = erase_node(node->rchild, key);
        node = erase_maintain(node);
    } else {
        if (node->lchild == NIL && node->rchild == NIL) {
            node->father && (NIL->black += node->black);
            free(node);
            return NIL;
        } else if (node->lchild == NIL || node->rchild == NIL) {
            RBTNode *temp = node->lchild == NIL ? node->rchild : node->lchild;
            temp->father = node->father;
            temp->black += node->black;
            free(node);
            return temp;
        } else {
            RBTNode *temp = predecessor(node);
            temp->key ^= node->key;
            node->key ^= temp->key;
            temp->key ^= node->key;
            node->lchild = erase_node(node->lchild, key);
            node = erase_maintain(node);
        }
    }
    if (node->father == NULL) {
        node->black = 1;
    }
    return node;
}

void inorder(RBTNode *node) {
    if (node == NULL || node == NIL) return;
    inorder(node->lchild);
    printf("%d(%d,%d,%d)\n", node->key, node->black, node->lchild->key, node->rchild->key);
    inorder(node->rchild);
}

int main() {
    init_NIL();
    RBTNode *root = NULL;
    int opr, n;
    while (scanf("%d%d", &opr, &n) != EOF) {
        switch (opr) {
            case 0:
                root = insert_node(root, n);
                break;
            case 1:
                root = erase_node(root, n);
                break;
        }
        printf("inorder:\n");
        inorder(root);
        printf("--------\n");
    }
    return 0;
}

