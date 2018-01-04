/*************************************************************************
	> File Name: 10.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月16日 星期六 08时23分35秒
 ************************************************************************/

#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Animal {
public :
    Animal(const string &a) : __name(a){}
    virtual void run() {
        cout << "i cannt run" << endl;
    } 
    //根据对象的具体方法执行
private :
    string __name;
};

class Cat : public Animal {
public :
    Cat() : Animal("cat") {}
    void run() override { //覆盖父类方法
        cout << "i can run" << endl;
    }
};

int main() {
    Cat a;
    Animal &b = a;
    Animal d("miao");
    a.run();
    b.run();
    return 0;
}

