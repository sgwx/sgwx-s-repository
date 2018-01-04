/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月12日 星期六 10时51分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}

typedef struct data {
    int val, ind;
} Data;

int cmp_data(Data a, Data b) {
    if (a.val < b.val) return 1;
    return 0;
}

void quick_sort(Data *arr, int l, int r) {
    while (r - l > 0) {
        int x = l, y = r;
        Data z = arr[l];
        while (x < y) {
            while (x < y && cmp_data(z, arr[y])) y--;
            if (x < y) arr[x++] = arr[y];
            while (x < y && cmp_data(arr[x], z)) x++;
            if (x < y) arr[y--] = arr[x];
        }
        arr[x] = z;
        quick_sort(arr, l, x - 1);
        l = x + 1;
    }
    return ;
}


int main() {
    srand(time(0));
    int n;
    scanf("%d", &n);
    Data *arr = (Data *)malloc(sizeof(Data) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].val);
        arr[i].ind = i;
    }
    quick_sort(arr, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%d(%d) ", arr[i].val, arr[i].ind);
    }
    free(arr);
    return 0;
}


