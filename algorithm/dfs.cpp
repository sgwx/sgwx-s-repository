/*************************************************************************
	> File Name: 10.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月29日 星期三 22时54分54秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    char **mat;
    int *vis;
    int n, m;
} Graph;

Graph *init(int n, int m) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->mat = (char **)malloc(sizeof(char *) * n);
    g->vis = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        g->mat[i] = (char *)calloc(m, sizeof(char));
    }
    g->n = n;
    g->m = m;
    return g;
}

int dfs(Graph *g, int t, int n) {
    if (n == g->n || t == 0) {
        if (t == 0) return 1;
        return 0;
    }
    int ans = 0;
    ans += dfs(g, t, n + 1);
    printf("ans : %d\n", ans);
    for (int i = 0; i < g->n; ++i) {
        if (g->vis[i]) continue;
        if (g->mat[n][i] == '.') continue;
        //printf("n : %d, i : %d, g->mat[i][j] : %c\n", n, i, g->mat[n][i]);
        g->vis[i] = 1;
        ans += dfs(g, t - 1, n + 1);
        printf("ans1 : %d\n", ans);
        g->vis[i] = 0;
    }
    return ans;
}
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == -1 && m == -1) break;
        Graph *g = init(n, n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", g->mat[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%c ", g->mat[i][j]);
            }
            printf("\n");
        }
        printf("%d\n", dfs(g, m, 0));
        free(g);
    }
    return 0;
}

