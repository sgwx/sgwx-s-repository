/*************************************************************************
	> File Name: 17.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月14日 星期四 20时46分19秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define MAX_N 20000

int rand() {
    int x = 10099;
    static int plus = 1;
    do {
        plus *= x;
        plus %= 10103;
    } while(plus > 10000);
    return plus;
}

int main() {
    int arr[10000] = {0};
    for (int i = 1; i <= 10000; ++i) {
        if (i % 20 == 0) {
            cout << endl;
        }
        cout << rand() << "  ";
        //int x = rand();
        //arr[x++];
        //if (arr[x] > 1) {
        //    cout << "error" << endl;
        //}
    }
    cout << endl;
    return 0;
}

