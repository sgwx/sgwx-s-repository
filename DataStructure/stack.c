/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月06日 星期日 11时04分56秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "stack.h"

int main () {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    char str[100];
    init(s, 100);
    
    int flag = 1;
    while (scanf("%c", &str) != EOF) {
        switch (str) {
            case '(' : {
                push_stack (s, str);
            }break;
            case '[' : {
                push_stack (s, str);
            }break;
            case '{' : {
                push_stack (s, str);
            }break;
            case ')' : {
                if (top(s) == str) {
                    pop(s);
                    break;
                } else {
                    flag = 0;
                    break;
                }
            }break;
            case ']' : {
                if (top(s) == str) {
                    pop(s);
                    break;
                } else {
                    flag = 0;
                    break;
                }
            } break;
            case '}' : {
                if (top(s) == str) {
                    pop(s);
                    break;
                } else {
                    flag = 0;
                    break;
                }
            } break;
        }
        if (flag == 0) {
            break;
        }
    }
    
    return 0;
}

