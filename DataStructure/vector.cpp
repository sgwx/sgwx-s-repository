/*************************************************************************
	> File Name: vector.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月02日 星期三 08时23分54秒
 ************************************************************************/

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include"test1.h"
using namespace std;


/*typedef struct node {
    int x, y;
} Node;
*/
#define ERROR 0
#define OK 1

typedef struct Vector {
    int size ,length;
    int *data;
} Vector;

int expand(Vector *vec) {
    int *temp = vec->data;
    vec->data = (int *)realloc(vec->data, vec->size * sizeof(int));
    if (vec->data == NULL) {
        vec->data = temp;
        return ERROR;
    }
    vec->size *= 2;
    return OK;
}

void init(Vector *vec, int n = 10) { 
    vec->data = (int *)malloc(n * sizeof(int));
    vec->size = n;
    vec->length = 0;
}

int insert(Vector *vec, int n, int index) {
    if (index < 0 || index > vec->length) {
        return ERROR;
    }
    if (vec->length == vec->size) {
        if (expand(vec) == ERROR) {
            return ERROR;
        }
    }
    for (int i = vec->length; i > index; --i) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = n;
    vec->length++;
    return n;
}

int delete_node(Vector *vec, int index) {
    if (index < 0 || index >= vec->length) {
        return ERROR;
    }
    for (int i = index; i < vec->length - 1; ++i) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->length--;
    return OK;
}

void output(Vector *vec) {
    if (vec->length) {
        printf("%d", vec->data[0]);
    }
    for (int i = 1; i < vec->length; ++i) {
        printf(" %d", vec->data[i]);
    }
}

void clear(Vector *vec) {
    if (!vec->length) return ;
    free(vec->data);
    free(vec);
} 

/*TEST (Vector, insert) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    int a;
    init(vec);
    for (int i = 0; i < 10; ++i) {
        a = insert(vec, i, i);
        ASSERT_EQ(a, i);
    }
}*/

int main() {
    
    
    
    
    
    
    return 0;
}

