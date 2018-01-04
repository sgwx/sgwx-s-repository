/*************************************************************************
	> File Name: shift_and.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月15日 星期二 18时35分18秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MC(T, n) (T*)malloc(sizeof(T) * n);

typedef struct Bitmap {
    int *data;
    int size;
} Bitmap;

Bitmap *init(int n = 1) {
    Bitmap *bm = (Bitmap *)malloc(1 * sizeof(Bitmap));
    bm->data = (int *)calloc(n, sizeof(int));
    bm->size = n;
    return bm;
}

void expand_bm(Bitmap *bm, int n) {
    int *data_temp = (int *)calloc(n, sizeof(int));
    memcpy(data_temp, bm->data, sizeof(int) * bm->size);
    free(bm->data);
    bm->data = data_temp;
    bm->size = n;
    return ;
}

int is_one(Bitmap *bm, int n) {
    if (n / 30 + 1 > bm->size) {
        expand_bm(bm, n / 30 + 1);
    }
    return bm->data[n / 30] & (1 << (n % 30));
}

void left_move(Bitmap *bm, int n) {
    is_one(bm, n);
    bm->data[0] <<= 1;
    for (int i = 1; i < bm->size; ++i) {
        bm->data[i] <<= 1;
        bm->data[i] |= !!(bm->data[i - 1] & (1 << 30));
    }
    return ;
}

void set_one(Bitmap *bm, int n) {
    if (n / 30 + 1 > bm->size) {
        expand_bm(bm, n / 30 + 1);
    }
    bm->data[n / 30] |= (1 << (n % 30));
    return ;
}

void add_one(Bitmap *bm1, Bitmap *bm2, int n) {
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

void shift_and(const char *s, const char *t) {
    Bitmap *str[256];
    for (int i = 0; i < 256; ++i) {
        str[i] = init();
    }
    int len = 0, times = 0;
    Bitmap *p = init();
    for (int i = 0; t[i]; ++i) {
        set_one(str[t[i]], i);
        len++;
        times++;
    }
    for (int i = 0; s[i]; ++i) {
        times++;
        left_move(p, len);
        set_one(p, 0);
        add_one(p, str[s[i]], len);
        if (is_one(p, len - 1)) {
            printf("shift_and Yes : %d\n", times);
            return ;
        }
    }
    printf("shift_and NO : %d\n", times);
    fflush(stdout);
    return ;
}

int main() {
    char s[] = "sgjshjfhgjsgfdfjgituuoipro[wqefgkdlfnc,bmlknmoijkhnkmkjkjgfbvcmazlzx]jhfjsfjihjrjiehirioegjkkrjgkkkadsdfhjkshgfhjdsfdkkfkjfdklk;slfmf";
    char t[] = "jhfjsfjihjrjiehirioegjkkrjgkkvhfdjsassbhkijjrwrhtrtrijk";
    char a[] = "guweiruhojjfldnbkmnsmz;zvfoowfjehrtjrgjkopjthu";
    char b[] = "kjgfbvcmazlzx]jhfjsfjihjrjiehir";
    shift_and(s, t);
    shift_and(s, b);
    shift_and(s, a);
    return 0;
}

