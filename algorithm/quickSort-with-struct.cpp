/*************************************************************************
	> File Name: 8.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月23日 星期四 18时36分08秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

typedef struct Node {
    int id, index;
} Node ;

void swap(Node *a, Node *b) {
    a->id = b->id;
    a->index = b->index;
}

void quick_sort(Node *a, int l, int r) {
    while (l < r) {
        int x = l, y = r;
        Node z;
        z.id = a[l].id;
        z.index = a[l].index;
        while (x < y) {
            while (x < y && a[y].id > z.id) y--;
            if (x < y) swap(&a[x++], &a[y]);
            while (x < y && a[x].id < z.id) x++;
            if (x < y) swap(&a[y--], &a[x]);
        }
        a[x].id = z.id;
        a[x].index = z.index;
        quick_sort(a, x + 1, r);
        r = x - 1;
    }
    return ;
}

int main() {
    int n, m;
    cin >> n >> m;
    Node a[n + 5];
    vector<int> temp;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].id);
        a[i].index = i;
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        temp.push_back(t);
    }
    quick_sort(a, 0, n - 1);
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << "id : " << a[i].id << " index : " << a[i].index << endl;
    }
    int ans[n + 5] = {0};
    sort(temp.begin(), temp.end());
    for (int i = 0; i < m; ++i) {
        cout << temp[i] << " ";
    }
    cout << endl;
    fflush(stdout);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i].id >= temp[j]) {
                int t = a[i].index;
                ans[t]++;
                temp[j] = INT_MAX;
                sum++;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}

