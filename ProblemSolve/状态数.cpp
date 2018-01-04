/*************************************************************************
	> File Name: 10.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 14时27分54秒
 ************************************************************************/


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define STATUS_N 1000000
#define MAX_N 10

int main() {
    int ans[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = STATUS_N - 1, status = 1, ind = 0;
    while (status <= n && ind < MAX_N) {
        ind++;
        status *= ind;
    }
    status /= ind;
    for (int i = MAX_N - ind; i < MAX_N && n; ++i) {
        ind--;
        int j = i + 1, k;
        while (n >= status && j < MAX_N) {
            k = ans[i], ans[i] = ans[j], ans[j] = k;
            j++;
            n -= status;
        }
        status /= ind;
    }
    for (int i = 0; i < MAX_N; ++i) {
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
