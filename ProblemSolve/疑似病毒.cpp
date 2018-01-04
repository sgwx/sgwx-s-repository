/*************************************************************************
> File Name: 11.cpp
> Author: 
> Mail: 
> Created Time: 2017年11月25日 星期六 12时49分15秒
************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define SIZE 4
#define MAX_N 500

typedef struct Node {
    int size, count;
    struct Node **childs, *fail;
} Node;

typedef struct matrix {
    int **data, n;
} matrix;

matrix *init_matrix(int n) {
    matrix *t = (matrix *)malloc(sizeof(matrix));
    t->data = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        t->data[i] = (int *)calloc(n, sizeof(int));
    }
    t->n = n;
    return t;
}

void clear_matrix(matrix *m) {
    free(m->data);
    free(m);
}

Node *init_node() {
    Node *t = (Node *)malloc(sizeof(Node));
    t->childs = (Node **)calloc(SIZE, sizeof(Node *));
    t->fail = NULL;
    t->size = 0;
    t->count = 0;
    return t;
}

void clear(Node *root) {
    if (root == NULL) return;
    for (int i = 0; i < SIZE; ++i) {
        if (root->childs[i]) clear(root->childs[i]);
    }
    free(root->childs);
    free(root);
}

int trans(char ch) {
    switch (ch) {
        case 'A' : return 0;
        case 'G' : return 1;
        case 'C' : return 2;
        case 'T' : return 3;
        default :
            printf("error\n");
        return -1;
    }
    return -1;
}

void insert_node(Node *root, char *buffer) {
    Node *p = root;
    int len = strlen(buffer);
    for (int i = 0; i < len; ++i) {
        if (p->childs[trans(buffer[i])] == NULL) {
            p->childs[trans(buffer[i])] = init_node();
        }
        p = p->childs[trans(buffer[i])];
    }
    p->count = 1;
    return ;
}

int build_automation(Node *root) {
    Node *q[MAX_N];
    int head = 0, tail = 0;
    q[tail++] = root;
    root->fail = root;
    root->size = 0;
    int id = 1;
    while (head < tail) {
        Node *p = q[head++];
        for (int i = 0; i < SIZE; ++i) {
            if (p->childs[i] == NULL) continue;
            Node *child = p->childs[i];
            Node *now = p;
            if (now == root) {
                child->fail = root;
            } else {
                while (now != root && now->fail->childs[i] == NULL) {
                    now = now->fail;
                }
                if (now->fail->childs[i] == NULL) {
                    p->childs[i]->fail = root;
                } else {
                    p->childs[i]->fail = now->fail->childs[i];
                    p->childs[i]->count += now->fail->childs[i]->count;
                }
            }
            p->childs[i]->size = id;
            id++;
            q[tail++] = p->childs[i];
        }
    }
    return id;
}

int count_sum(int x, int sum) {
    while (x >= sum * 3) {
        x -= sum;
    }
    return x;
}

void __count_matrix(matrix *m, Node *root, Node *p, int i, int j, int id) {
    Node *now = p->fail;
    while (now != root && now->childs[i] == NULL) {
        now = now->fail;
    }
    int t1 = count_sum(p->size + id * j, id);
    int t2 = count_sum(now->size + id * j, id);
    if (now->childs[i] == NULL) {
        m->data[t1][t2]++;
    } else {
        int temp = (now->childs[i]->size + id * (j + now->childs[i]->count));
        int t3 = count_sum(temp, id);
        m->data[t1][t3]++;
    }
    return ;
}

void multi(matrix *a, matrix *b) {
    matrix *temp = init_matrix(a->n);
    for (int i = 0; i < a->n; i++) {
        for (int j = 0; j < a->n; j++) {
            int ans = 0;
            for (int k = 0; k < a->n; k++) {
                temp->data[i][j] += a->data[i][k] * b->data[k][j];
                temp->data[i][j] %= 10007;
            }
            temp->data[i][j] %= 10007;
        }
    }
    int **temp_data = a->data;
    a->data = temp->data;
    temp->data = temp_data;
    clear_matrix(temp);
    return ;
}

void quick_mi(matrix *a, matrix *b, int n) {
    while (n) {
        if (n & 1) multi(a, b);
        multi(b, b);
        n >>= 1;
    }
    return ; 
}

matrix *count_matrix(Node *root, int id) {
    matrix *m = init_matrix(id * 3);
    Node *q[MAX_N];
    int sum = id;
    int head = 0, tail = 0;
    q[tail++] = root;
    //int time = 1;
    int t;
    while (head < tail) {
        Node *p = q[head++];
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (p->childs[i] == NULL) {
                    __count_matrix(m, root, p, i, j, id);
                    continue;
                } else {
                    int t1 = count_sum(p->size + id * + j, id);
                    int t2 = count_sum(p->childs[i]->size + id * (p->childs[i]->count + j), id);
                    m->data[t1][t2]++;
                }
            }
            if (p->childs[i] != NULL) {
                q[tail++] = p->childs[i];
            }
        }
    }
    return m;
}

void copy_matrix(matrix *m1, matrix *m2) {
    for (int i = 0; i < m1->n; ++i) {
        for (int j = 0; j < m1->n; ++j) {
            m2->data[i][j] = m1->data[i][j];
        }
    }
    return ;
}

int main() {
    int n, t;
    while (cin >> n >> t) {
        //cin >> n >> t;
        Node *root = init_node();
        for (int i = 0; i < n; ++i) {
            char str[10];
            cin >> str;
            insert_node(root, str);
        }
        int id = build_automation(root);
        matrix *m = count_matrix(root, id);
        matrix *m1 = init_matrix(m->n);
        copy_matrix(m, m1);
        quick_mi(m, m1, t - 1);
        int ans = 0;
        for (int i = 2 * id; i < 3* id; ++i) {
            ans += m->data[0][i];
            ans %= 10007;
        }
        cout << endl;
        cout << "ans : " << ans << endl;
        cout << "      ";
        for (int i = 0; i < m->n; ++i) {
            if (i < 10) {
                cout << i << "  ";
            } else {
                cout << i << " ";
            }
        }
        cout << endl;
        cout << "  ";
        for (int i = 0; i < m->n; ++i) {
            cout << " -";
        }
        cout << endl;
        for (int i = 0; i < m->n; ++i) {
            printf("%2d | ", i);
            for (int j = 0; j < m->n; ++j) {
                printf("%2d|", m->data[i][j]);
            }
            cout << endl;
        }
    }
    return 0;
}

