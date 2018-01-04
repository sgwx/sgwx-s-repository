/*************************************************************************
> File Name: 2.cpp
> Author: 
> Mail: 
> Created Time: 2017年09月06日 星期三 15时23分06秒
************************************************************************/

#include <iostream>
#include <string>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T>
struct array {
    array(int size) {
        this->data = new T[size];
        this->size = size;
    }
    T& operator[](const int ind) {
        if (ind < 0 || ind >= this->size) {
            cout << "segment fault ! but I am xiaoqiang !" << endl;
            return this->nil;
        } else {
            return this->data[ind];
        }
    }
    void reserve(int n) {
        if (n < 0 || n >= this->size) {
            n = this->size;
        }
        for (int i = 0; i < n / 2; ++i) {
            this->data[i] ^= this->data[n - i - 1];
            this->data[n - i - 1] ^= this->data[i];
            this->data[i] ^= this->data[n - i - 1];
        }
    }
    T nil;
    T *data;
    int size;
};

int main() {
    array<int> a(100);
    array<double> b(100);
    array<string> c(100);
    for (int i = 0; i < 5; i++) {
        int n;
        cin >> n;
        a[i] = n;
    }
    a.reserve(5); 
    for (int i = 0; i < 5; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}

