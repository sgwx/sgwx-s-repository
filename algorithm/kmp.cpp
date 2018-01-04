/************************************************************************
	> File Name: 17.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月15日 星期二 08时29分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_next(char *t, int *next) { 
    next[0] = -1;
    int j = 1, match = -1;
    while (t[j]) {
        while (match != -1 && t[match + 1] != t[j]) {
            match = next[match];
        }
        if (t[match + 1] == t[j]) {
            next[j] = match + 1;
            match++;
        } else {
            next[j] = match;
        }
        j++;
    }
    return ;
}

void kmp_match(char *s, char *t, int *next) {
    int i = 0, j = -1;
    while (s[j]) {
        while (j != -1 && t[j + 1] != s[i]) {
            j = next[j];
        }
        if (t[j + 1] == s[i]) {
            j++;
        }
        if (t[j + 1] == '\0') {
            printf("KMP YES\n");
            return ;
        }
        i++;
    }
    printf("KMP NO\n");
    return ;
}

void sunday(char *s, char *t) {
    int str_index[256] = {0};
    int len = strlen(t);
    int s_len = strlen(s);
    for (int i = 0; i < 256; ++i) {
        str_index[i] = len + 1;
    }
    for (int i = 0; t[i]; i++) {
        str_index[t[i]] = len - i;
    }
    int i = 0, j = 0;
    int times = 0;
    while (i + len <= s_len) {
        if (s[i + j] != t[j]) {
            times += 2;
            i += str_index[s[i + len]];
            j = 0;
        } else {
            times += 2;
            j++;
        }
        if (t[j] == '\0') {
            printf("Sunday YES : %d\n", times);
            return ;
        }
    }
    printf("Sunday NO : %d\n", times);
    return;        
}

void shift_and(char *s, char *t) {
    int str_encode[256] = {0};
    int p = 0, len = 0, times = 0;
    for (int i = 0; t[i]; ++i) {
        str_encode[t[i]] |= (1 << i);
        len++;
        times++;
    }
    for (int i = 0; s[i]; ++i) {
        p = (p << 1 | 1) & str_encode[s[i]];
        times++;
        if (p & (1 << (len - 1))) {
            printf("shift_and YES : %d\n", times);
            return ;
        }
    }
    printf("shift_and NO : %d\n", times);
    return ;
}

int main() {
    char s[] = "aaa";
    char t[] = "aaa";
    sunday(s, t);
    return 0;
}




