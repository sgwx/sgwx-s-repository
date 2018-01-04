/*************************************************************************
	> File Name: 9.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 13时42分37秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#define MOD 1000

int main() {
    int ans[1000] = {0};
    ans[0] = 1, ans[1] = 1;
    for (int i = 0; i < 100; ++i) {
        for (int j = 1; j <= ans[0]; ++j) {
            ans[j] *= 1024;
        }
        for (int j = 1; j <= ans[0]; ++j) {
            if (ans[j] < MOD) continue;
            ans[j + 1] += ans[j] / MOD;
            ans[j] %= MOD;
            if (j == ans[0]) ++ans[0];
        }
    }
    int t = 0;
    for (int i = 1; i <= ans[0]; ++i) {
        while (ans[i]) {
            t += ans[i] % 10;
            ans[i] /= 10;
        }
    }
    printf("%d\n", t);
    return 0;
}
