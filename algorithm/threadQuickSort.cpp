/*************************************************************************
> File Name: temp.cpp
> Author: 上官文雄
> Mail: sgwx1996@163.com
> Created Time: 2017年09月26日 星期二 20时23分52秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct QuickSortArg {
    int *num;
    int length;
} QuickSortArg;

typedef struct ThreadManagerArg {
    int *num;
    int length;
    int k;
} ThreadManagerArg;

int quick_select(int *num, int n) {
    int x = 0, y = n - 1;
    int z = num[rand() % n];
    do {
        while (num[x] < z) x++;
        while (num[y] > z) y--;
        if (x <= y) {
            if (x != y) {
                num[x] ^= num[y];
                num[y] ^= num[x];
                num[x] ^= num[y];
            }
            x++, y--;
        }
    } while (x <= y);
    return y;
}

void quick_sort(int *num, int left, int right) {
    while (right - left >= 1) {
        int x;
        x = quick_select(num + left, right - left + 1) + left;
        quick_sort(num, x + 1, right);
        right = x;
    }
    return ;
}

void *thread_quick_sort(void *arg) {
    QuickSortArg *r_arg = (QuickSortArg *)arg;
    quick_sort(r_arg->num, 0, r_arg->length - 1);
    free(r_arg);
    return NULL;
}

void *thread_manager(void *ARG) {
    ThreadManagerArg *arg = (ThreadManagerArg *)ARG;
    if (arg->length <= 1) return NULL;
    pthread_t thread[2];
    if (arg->k == 0) {
        quick_sort(arg->num, 0, arg->length - 1);
    } else if (arg->k <= 1) {
        int x = quick_select(arg->num, arg->length);
        QuickSortArg *temp_arg;
        temp_arg = (QuickSortArg *)malloc(sizeof(QuickSortArg));
        temp_arg->num = arg->num;
        temp_arg->length = x + 1;
        pthread_create(thread + 0, NULL, thread_quick_sort, temp_arg);
        temp_arg = (QuickSortArg *)malloc(sizeof(QuickSortArg));
        temp_arg->num = arg->num + x + 1;
        temp_arg->length = arg->length - x - 1;
        pthread_create(thread + 1, NULL, thread_quick_sort, temp_arg);
        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
    } else {
        int x = quick_select(arg->num, arg->length);
        ThreadManagerArg *temp_arg;
        temp_arg = (ThreadManagerArg *)malloc(sizeof(ThreadManagerArg));
        temp_arg->num = arg->num;
        temp_arg->length = x + 1;
        temp_arg->k = arg->k - 1;
        pthread_create(thread + 0, NULL, thread_manager, temp_arg);
        temp_arg = (ThreadManagerArg *)malloc(sizeof(ThreadManagerArg));
        temp_arg->num = arg->num + x + 1;
        temp_arg->length = arg->length - x - 1;
        temp_arg->k = arg->k - 1;
        pthread_create(thread + 1, NULL, thread_manager, temp_arg);
        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
    }
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int *num = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    int begin = clock();
    ThreadManagerArg *temp_arg;
    temp_arg = (ThreadManagerArg *)malloc(sizeof(ThreadManagerArg));
    temp_arg->num = num;
    temp_arg->length = n;
    temp_arg->k = atoi(argv[1]);
    thread_manager(temp_arg);
    int end = clock();
    fprintf(stderr, "%lf s\n", 1.0 * (end - begin) / CLOCKS_PER_SEC);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    return 0;
}
