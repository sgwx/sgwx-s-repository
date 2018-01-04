/*************************************************************************
	> File Name: 26.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月26日 星期二 18时15分20秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct file_write{
    char *filename;
    int n;
}file_write;

void *thread_write_file(void *arg) {
    file_write *temp = (file_write *) arg;
    FILE *fpout = fopen(temp->filename, "w");
    for (int i = 0; i < temp->n; ++i) {
        fprintf(fpout, "%d\n", i);
    }
    printf("write success\n");
    fclose(fpout);
    return NULL;
}

int main() {
    char filename[100];
    int n;
    pthread_t thread[2];
    while (scanf("%s%d", filename, &n) != EOF) {
        file_write *F = (file_write *)malloc(sizeof(file_write));
        F->filename = strdup(filename);
        F->n = n;
        pthread_create(thread + 0, NULL, thread_write_file, F);
    }
    return 0;
}

