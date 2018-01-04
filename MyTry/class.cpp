/*************************************************************************
	> File Name: 17.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月12日 星期二 18时26分01秒
 ************************************************************************/

#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Animal {
public :
    Animal(string name) : __name(name) {}
    void tell_me_your_name() {
        cout << "my name is " << this->__name << endl;
    }
    void set_name(string name) {
        this->__name = name;
    }
protected :
    string __name;
};

class Cat : public Animal{
public :
    Cat() : Animal("cat1") {}
};

class HasTailCat : public Cat {
public:
    HasTailCat(string name) {
        this->__name = name;
    }
};

int main() {
    Cat a;
    a.tell_me_your_name();
    return 0;
}

