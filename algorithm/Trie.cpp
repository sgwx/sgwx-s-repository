/*************************************************************************
	> File Name: 26.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月27日 星期三 09时21分42秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int flag;
    struct Node *next[26];
} Node;

Node *get_node() {
    Node *p = (Node *)calloc(1, sizeof(Node));
    return p;
}

int insert(Node *tree, char *str) {
    Node *p = tree;
    while (str[0]) {
        if (p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = get_node();
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return 1;
}

void output(Node *tree, int ind, char *str) {
    if (tree == NULL) return ;
    for (int i = 25; i >= 0; --i) {
        if (tree->next[i] == NULL) continue;
        str[ind] = 'a' + i;
        output(tree->next[i], ind + 1, str);
    }
    if (tree->flag) {
        printf("%s\n\n", str);
    }
    return ;
}

void clear(Node *tree) {
    f (tree == NULL) return ;
    for (int i = 0; i < 26; ++i) {
        clear(tree->next[i]);
    }
    free(tree);
}

int main() {
    Node *tree = get_node();
    int n;
    char str[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        insert(tree, str);
    }
    char ans[100];
    output(tree, 0, ans);
    clear(tree);
    return 0;
}

