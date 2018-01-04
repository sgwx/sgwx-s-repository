/*************************************************************************
	> File Name: shift_and_plus.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月17日 星期四 22时31分45秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bitmap {
    int *data;
    int size;
} Bitmap;

Bitmap *init(int n = 1) {
    Bitmap *bm = (Bitmap *)malloc(sizeof(Bitmap) * n);
    bm->data = (int *)calloc(n, sizeof(int));
    bm->size = n;
    return bm;
}

void expand_bm(Bitmap *bm, int n) {
    int *temp_data = (int *)calloc(n, sizeof(int));
    memcpy(temp_data, bm->data, sizeof(int) * bm->size);
    free(bm->data);
    bm->data = temp_data;
    bm->size = n;
    return ;
}

int is_one(Bitmap *bm, int n) {
    if (n / 30 + 1 > bm->size) {
        expand_bm(bm, n / 30 + 1);
    }
    return bm->data[n / 30] & (1 << (n % 30));
}

void set_one(Bitmap *bm, int n) {
    is_one(bm, n);
    bm->data[n / 30] |= (1 << (n % 30));
    return ;
}

void left_move(Bitmap *bm, int n) {
    is_one(bm, n);
    //bm->data[0] <<= 1;
    for (int i = 0; i < bm->size; ++i) {
        bm->data[i] <<= 1;
        bm->data[i] |= !!(bm->data[i - 1] & (1 << 30));
    }
    return ;
}

void and_one(Bitmap *bm1, Bitmap *bm2, int n) {
    is_one(bm1, n);
    is_one(bm2, n);
    int index = 0, i = 0;
    while (index <= n) {
        bm1->data[i] &= bm2->data[i];
        i++;
        index += 30;
    }
    return ;
}

void clear(Bitmap *bm) {
    free(bm->data);
    free(bm);
}

void shift_and_plus(const char *s, const char *t) {
    Bitmap *str[256];
    for (int i = 0; i < 256; ++i) {
        str[i] = init();
    }
    Bitmap *p = init();
    int times = 0, len = 0;
    for (int i = 0; t[i]; ++i) {
        set_one(str[t[i]], i);
        len++;
        times++;
    }
    for (int i = 0; s[i]; ++i) {
        times++;
        left_move(p, len);
        set_one(p, 0);
        and_one(p, str[s[i]], len);
        if (is_one(p, len - 1)) {
            printf("Shift_and Yes : times :%d\n", times);
            return ;
        }
    }
    printf("Shift_and No : times :%d\n", times);
    return ;
}

int main() {
    char s[2000];
    char t[2000];
    scanf("%s%s", s, t);
    shift_and_plus(s, t);
    return 0;
}

