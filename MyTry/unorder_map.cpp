/*************************************************************************
	> File Name: unordered_map.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年09月05日 星期二 18时41分00秒
 ************************************************************************/

#include<iostream>
#include<queue>
#include<string>
#include<stack>
#include<unordered_map>

//using namespace std; //不建议使用
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::unordered_map;

template<typename T>
void swap(T &a, T &b) {
    T c;
    c = a;
    a = b;
    b = c;
}

int main() {
    unordered_map<string, double> h;
    string opr;
    while (cin >> opr) {
        if (opr == "insert") {
            string name;
            double height;
            cin >> name >> height;
            h[name] = height;
        } else if (opr == "search") {
            string name;
            cin >> name;
            cout << h[name] << endl;
        } else if (opr == "end") {
            break;
        }
    }
    return 0;
}

