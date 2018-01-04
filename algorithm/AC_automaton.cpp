/*************************************************************************
    > File Name: 16.cpp
    > Author: 
    > Mail: 
    > Created Time: 2017年11月18日 星期六 19时50分07秒
************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';
const int MAX_N = 10005;


typedef struct TrieNode {
    int count;
    struct TrieNode **childs;
    struct TrieNode *fail;
} TrieNode, *Trie;

TrieNode* new_node() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->childs = (TrieNode **)malloc(sizeof(TrieNode*) * MAX_N);
    for (int i = 0; i < 26; ++i) {
        node->childs[i] = NULL;
    }
    node->count = 0;
    node->fail = NULL;
    return node;
}

void clear(TrieNode *node) {
    if (node == NULL) return;
    for (int i = 0; i < 26; ++i) {
        if (node->childs[i]) clear(node->childs[i]);
    }
    free(node->childs);
    free(node);
}

void insert(TrieNode *root, char *pattern) {
    TrieNode *p = root;
    while (*pattern) {
        if (p->childs[pattern[0] - BASE] == NULL)  {
            p->childs[pattern[0] - BASE] = new_node();
        }
        p = p->childs[pattern[0] - BASE];
        ++pattern;
    }
    p->count++;
}
void build_automaton(TrieNode *root) {        
    TrieNode *p, *now;
    TrieNode *q[MAX_N];
    int head = 0, tail = 0;
    q[tail++] = root;
    while (head < tail) {
        p = q[head++];
        for (int i = 0; i < 26; ++i) {
            if (p->childs[i] == NULL) continue;
            now = p->fail;
            while (now != NULL && now->childs[i] == NULL) {
                now = now->fail;
            }
            if (now == NULL) {
                p->childs[i]->fail = root;
            } else {
                p->childs[i]->fail = now->childs[i];
            }
            q[tail++] = p->childs[i];
        }
    }
}

int match_count(TrieNode *root, char *buffer) {
    TrieNode *p = root, *now;
    int total_count = 0;
    while (*buffer) {
        while (p && p->childs[buffer[0] - BASE] == NULL) {
            p = p->fail;
        }
        if (p == NULL) {
            p = root;
        } else {
            p = p->childs[buffer[0] - BASE];
        }
        now = p;
        while (now != root) {
            total_count += now->count;
            now = now->fail;
        }
        ++buffer;
    }
    return total_count;
}

int main() {
    int n;
    scanf("%d", &n);
    TrieNode *root = new_node();
    for (int i = 0; i < n; ++i) {
        char *pattern = (char *)malloc(sizeof(char) * MAX_N);
        scanf("%s", pattern);
        insert(root, pattern);
        free(pattern);
    }
    char *buffer = (char *)malloc(sizeof(char) * MAX_N);
    scanf("%s", buffer);
    build_automaton(root);
    printf("%d\n", match_count(root, buffer));
    clear(root);
    free(buffer);
    return 0;

}


