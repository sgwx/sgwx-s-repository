/*************************************************************************
	> File Name: 25.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月24日 星期日 14时53分08秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void sunday(char *s, char *t) {
    int str_index[256] = {0};
    int len_t = strlen(t);
    int len_s = strlen(s);
    for (int i = 0; i < 256; ++i) {
        str_index[i] = len_t + 1;
    }
    for (int i = 0; t[i]; ++i) {
        str_index[t[i]] = len_t - i;
    }
    int i = 0, j = 0;
    while (i + len_t <= len_s) {
        if (s[i + j] != t[j]) {
            i += str_index[s[i + len_t]];
            j = 0;
        } else {
            j++;
        }
        if (j == len_t) {
            printf("sunday Yes\n");
            return ;
        }
    }
    printf("sunday No\n");
    return ;
}

void shift_and(char *s, char *t) {
    int s_index[256] = {0};
    int p = 0;
    int len = strlen(t);
    for (int i = 0; t[i]; ++i) {
        s_index[t[i]] |= (1 << i);
    }
    for (int i = 0; s[i]; ++i) {
        p = (p << 1 | 1) & s_index[s[i]];
        if (p & (1 << (len - 1))) {
            printf("shift_and Yes\n");
            return ;
        }
    }
    printf("shift_and No\n");
    return ;
}


int main() {
    char *s = "shanggua nwen xiong";
    char *t = "wenxiong";
    sunday(s, t);
    shift_and(s, t);
    return 0;
}

