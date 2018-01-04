/*************************************************************************
> File Name: expression.cpp
> Author: 
> Mail: 
> Created Time: 2017年11月21日 星期二 20时58分29秒
************************************************************************/

#include <iostream>
#include <math.h>
#include <string.h>
#include <cstdio>
using namespace std;

#define LOL (long long)(1e9 + 7)

long long my_in(char *str, int left, int right, int a) {
    int basics = 0;
    int min = 100000, ind = -1;
    for (int i = left; i < right; ++i) {
        if (str[i] == '(') { basics += 100; continue;  }
        if (str[i] == ')') { basics -= 100; continue;  }
        int thiss = 200000;
        if (str[i] == '+') thiss = basics + 1;
        if (str[i] == '-') thiss = basics + 1;
        if (str[i] == '*') thiss = basics + 2;
        if (str[i] == '/') thiss = basics + 2;
        if (str[i] == '^') thiss = basics + 3;
        if (min >= thiss) {
            min = thiss;
            ind = i;
        }
    }
    if (ind == -1) {
        int x = 0;
        for (int i = left; i < right; ++i) {
            if (str[i] == 'a') return a;
            if (str[i] < '0' || str[i] > '9') continue;
            x = x * 10 + (str[i] - '0');
        }
        return x;
    }
    long long mi = my_in(str, left, ind, a);
    long long mj = my_in(str, ind + 1, right, a);
    switch (str[ind]) {
        case '+' : return (mi + mj) % LOL;
        case '-' : return (mi - mj) % LOL;
        case '*' : return (mi * mj) % LOL;
        case '/' : return (mi / mj) % LOL;
        case '^' : return ((long long)powl(mi, mj)) % LOL;
    }
    return 0;
}

int main() {
    char str[100];
    char AA[26][100];
    int n;
    scanf("%[^\n]s", str);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        getchar();
        scanf("%[^\n]s", AA[i]);
    }
    for (int i = 0; i < n; ++i) {
        int flag = 1;
        for (int j = 0; j < 5; ++j) {
            if (my_in(str, 0, strlen(str), j) != my_in(AA[i], 0, strlen(AA[i]), j)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            printf("%c", i + 'A');        
        }
    }
    printf("\n");
    return 0;
}
