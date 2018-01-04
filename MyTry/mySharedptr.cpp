/*************************************************************************
    > File Name: 16.cpp
    > Author: 
    > Mail: 
    > Created Time: 2017年12月21日 星期四 21时14分22秒
************************************************************************/

#include<bits/stdc++.h>
using namespace std;


template<typename T>
struct shared_ptr1 {
    shared_ptr1() {
        cnt = nullptr;
        obj = nullptr;
        cout << "ccc" << endl;
    }
    shared_ptr1(T *obj) : obj(obj){
        cout << "constructor" << endl;
        cnt = new int;
        *cnt = 1;
    }
    template<typename U>
    shared_ptr1(shared_ptr1<U> &a) : obj(a.obj) {
        cnt = a.cnt;
        if (cnt) *cnt += 1;
    }
    template<typename U>
    shared_ptr1(shared_ptr1<U> &&a) {
        this->obj = a.obj;
        cnt = a.cnt;
        a.obj = nullptr;
        if (cnt) *cnt += 1;
    }
    shared_ptr1(const shared_ptr1<T> &a) {
        cout << "left copy" << endl;
        this->obj = a.obj;
        this->cnt = a.cnt;
        if(cnt) *cnt += 1;
    }
    shared_ptr1(shared_ptr1<T> &&a) {
        cout << "right copy" << endl;
        this->obj = a.obj;
        a.obj = nullptr;
    }
    ~shared_ptr1() {
        if (cnt) {
            *cnt--;
            if (cnt == 0) {
                delete obj;
                delete cnt;
            }
            obj = nullptr;
            cnt = nullptr;
        }
    }
    T *get() { return this->obj;  }
    int use_count() {
        if (cnt) return *cnt;
        return 0;
    }
    int *cnt;
    T *obj;
};


struct C {
    C() {}
    ~C() {}
};

struct D : C{
    D() {}
    ~D() {}
};


struct A {
    A() {} 
    A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n";  }
    A(int& n)  { std::cout << "lvalue overload, n=" << n << "\n";  }

};

class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
    a1_{std::forward<T1>(t1)},
    a2_{std::forward<T2>(t2)},
    a3_{std::forward<T3>(t3)}
    {
    }
private:
    A a1_, a2_, a3_;
};


template<typename T>
shared_ptr1<T> make_shared1() {
    //cout << "111" << endl;
    return shared_ptr1<T>(new T);
}

template<typename T, class... U>
shared_ptr1<T> make_shared1(U&&... u) {
    //cout << "222" << endl;
    return shared_ptr1<T>(new T(std::forward<U>(u)...));
}

int main() {
    //shared_ptr1<A> p1 = make_shared1<A>();
    //shared_ptr1<B> p2();
    shared_ptr1<A> p1 = make_shared1<A>(); // rvalue
    int i = 1;
    shared_ptr1<A> p3(p1);
    shared_ptr1<A> p2 = make_shared1<A>(i); // lvalue
    std::cout << "B\n";
    shared_ptr1<B> t = make_shared1<B>(2, i, 3);
    shared_ptr1<C> a = make_shared1<D>();
}

