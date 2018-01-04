/*************************************************************************
	> File Name: queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 08时43分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "test1.h"
#include "queuetest.h"


int main() {
    srand(time(0));
    Queue *q = (Queue *)malloc(sizeof(Queue));
    init_queue(q, 100);
    char ch;
    while (scanf("%s", &ch) != EOF) {
        int left_num = 0, right_num = 0;
        
    } 
    clear_queue(q);
    return 0;
}
