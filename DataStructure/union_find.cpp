/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月21日 星期二 14时09分33秒
 ************************************************************************/


#include <cstdio>
#include <cstdlib>

typedef struct UnionSet {
    int *father, size;
    int *count;
} UnionSet;

UnionSet *init(int size) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * size);
    u->count = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        u->father[i] = i;
        u->count[i] = 1;
    }
    return u;
}

int find(UnionSet *u, int node) {
    if (u->father[node] != node) {
        return find(u, u->father[node]);
    }
    return u->father[node];
}

int find_father(UnionSet *u, int node) {
    int ans = 1;
    while (u->father[node] != node) {
        ans++;
        node = u->father[node];
    } 
    return ans;
}

void merge_node(UnionSet *u, int node1, int node2, int key) {
    int ans1 = find(u, node1);
    int ans2 = find(u, node2);
    if (ans1 != ans2) {
        u->father[node2] = node1;
        u->count[node2] = key;
    } else {
        int temp1 = find_father(u, node1);
        int temp2 = find_father(u, node2);
        if (temp1 * key < u->count[node2] * temp2) {
            u->father[node2] = node1;
            u->count[node2] = temp1 * key;
        } else if (temp2 * key < u->count[node1] * temp1) {
            u->father[node1] = node2;
            u->count[node1] = temp2 * key;
        }
    }
}

int main() {
    int n, m, a, b, key;
    scanf("%d%d", &n, &m);
    UnionSet *u = init(n + 1);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &key);
        merge_node(u, a, b, key);
    }
    int ans = 0;
    int temp = find(u, 1);
    printf("\n");
    for (int i = 1; i <= n; ++i) {
        printf("u->count[%d] : %d\n", i, u->count[i]);
        ans += u->count[i];
    }
    printf("\n%d\n", ans - u->count[temp]);
    return 0;
}
