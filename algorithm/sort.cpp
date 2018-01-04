/*************************************************************************
	> File Name: sort.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月12日 星期六 14时50分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}

int cmp_value(int a, int b) {
    if (a < b) return 1;
    return 0;
}

void insert_sort(int *arr, int len) {
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (cmp_value(arr[j], arr[j - 1])) {
                swap(arr[j], arr[j - 1]);
            } else break;
        }
    }
}

void bubble_sort(int *arr, int len) {
    int times = 1;
    for (int i = len - 1; i >= 1 && times; --i) {
        times = 0;
        for (int j = 1; j <= i; ++j) {
            if (cmp_value(arr[j], arr[j - 1])) {
                swap(arr[j], arr[j - 1]);
                times++;
            }
        }
    }
}

void merge_sort(int *arr, int l, int r) {
    if (r <= l) return;
    if (r - l == 1) {
        if (cmp_value(arr[r], arr[l])) {
            swap(arr[r], arr[l]);
        }
        return ;
    }
    int mid = (l + r) / 2;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int ind1 = l, ind2 = mid + 1;
    int k = 0;
    while (ind1 <= mid || ind2 <= r) {
        if (ind1 > mid) {
            temp[k++] = arr[ind2++];
        } else if(ind2 > r) {
            temp[k++] = arr[ind1++];
        } else if(cmp_value(arr[ind1], arr[ind2])) {
            temp[k++] = arr[ind2++];
        } else {
            temp[k++] = arr[ind1++];
        }
    }
    for (int i = l; i <= r; ++i) {
        arr[i] = temp[i - l];
    }
    free(temp);
    return ;
}

/*void select_sort(int *arr, int n) {
    int temp;
    for (int i = 0; i < n; ++i) {
        temp = i;
        for (int j = i; j < n; ++j) {
            if (cmp_value(arr[temp], arr[j])) {
                temp = j;
            }
        }
        swap(arr[temp], arr[i]);
    }
}

void quick_sort(int *arr, int l, int r) {
    while (r - l > 0) {
        int x = l, y = r;
        int temp = rand() % (r - l + 1);
        swap(arr[l], arr[temp + l]);
        int z = arr[l];
        while (x < y) {
            while (x < y && cmp_value(z, arr[y])) y--;
            if (x < y) arr[x++] = arr[y];
            while (x < y && cmp_value(arr[x], z)) x++;
            if (x < y) arr[y--] = arr[x];
        }
        arr[x] = z;
        quick_sort(arr, x + 1, r);
        r = x - 1;
    }
    return ;
}

int main() {
    srand(time(0));
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }
    quick_sort(arr, 0, n - 1);
    //select_sort(arr, n);
    //insert_sort(arr, n);
    //merge_sort(arr, 0, n - 1);
    //bubble_sort(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}*/

