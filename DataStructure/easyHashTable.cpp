/*************************************************************************
	> File Name: 22.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月16日 星期六 11时28分50秒
 ************************************************************************/

#include<iostream>

using std::cin;
using std::cout;
using std::endl;

class HashFunc {
public :
    virtual int operator()(const void *data) const {
        const char *str = static_cast<const char *>(data);
        int hash = 0;
        for (int i = 0; str[i]; ++i) {
            hash = (hash << 5) ^ str[i] ^ (hash >> 3);
        }
        return (hash & 0x7fffffff);
    }
    virtual int operator()(int data) const {
        return data << 3;
    }
    virtual int operator()(double data) const {
        return (data / 5.3 * 3);
    }
};

class HashTable {
public :
    HashTable(const HashFunc &func) : __func(&func) {}
    int get_hash(const void *data) {
        return (*(this->__func))(data);
    }
    int get_hash(int data) {
        return (*(this->__func))(data);
    }
    int get_hash(double data) {
        return (*(this->__func))(data);
    }
private :
    const HashFunc *__func;
};

class my_HashFuc : public HashFunc {
public :
    int operator()(const void *data) const override {
        const char *str = static_cast<const char *>(data);
        int hash = 0;
        for (int i = 0; str[i]; ++i) {
            hash = (hash << 7) ^ str[i] ^ (hash >> 5);
        }
        return (hash & 0x7fffffff);
    }
    int operator()(int data) const override {
        return (data << 5 ^ data >> 3);
    }
    int operator()(double data) const override {
        return (data / 5.3 * 3);
    }
};

int main() {
    HashFunc hf;
    HashTable ht(hf);
    cout << ht.get_hash("haizei") << endl;
    my_HashFuc hf1;
    HashTable ht2(hf1);
    cout << ht2.get_hash(789) << endl;
    my_HashFuc hf3;
    HashTable ht3(hf3);
    cout << ht3.get_hash(50) << endl;
    return 0;
}

