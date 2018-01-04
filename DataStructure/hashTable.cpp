/*************************************************************************
> File Name: 23.cpp
> Author: 上官文雄
> Mail: sgwx1996@163.com
> Created Time: 2017年09月17日 星期日 08时37分27秒
************************************************************************/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;

template<typename KEY_T, typename VALUE_T>
struct Node {
    KEY_T key;
    VALUE_T value;
    Node *next;
    Node& operator= (const VALUE_T &v) {
        this->value = v;
        return *this;
    }
};

template<typename T> struct Hash;
template<> struct Hash<int> {
    int operator()(int a) {
        return a & 0x7fffffff;
    }
};
template<> struct Hash<double> {
    int operator()(double a) {
        return static_cast<int>(a) & 0x7fffffff;
    }
};
template<> struct Hash<string> {
    int operator()(const string &s) {
        int hash = 0;
        for (int i = 0; i < s.length(); i++) {
            hash = (hash << 5) ^ s[i] ^ (hash >> 3);
        }
        return (hash & 0x7fffffff);
    }
};
template<typename KEY_T, typename VALUE_T, typename HashFunc_T = Hash<KEY_T>>
class HashTable {
public :
    HashTable(int size = 10) : __size(size) {
        this->__data = new Node<KEY_T, VALUE_T>[this->__size];
        for (int i = 0; i < this->__size; ++i) {
            this->__data[i].next = nullptr;
        }
    }
    ~HashTable() {
        for (int i = 0; i < this->__size; ++i) {
            if (this->__data[i].next == nullptr) continue;
            Node<KEY_T, VALUE_T> *p = this->__data[i].next;
            while (p) {
                Node<KEY_T, VALUE_T> *temp = p;
                p = p->next;
                delete temp;
            }
        }
        delete[] this->__data;
    }
    Node<KEY_T, VALUE_T> &operator[](const KEY_T &key) {
        Node<KEY_T, VALUE_T> *temp = find(key);
        if (temp == this->end()) {
            int hash_code = this->__hash_func(key);
            int index = hash_code % this->__size;
            Node<KEY_T, VALUE_T> *p = &(this->__data[index]);
            while (p->next != nullptr) {p = p->next;}
            Node<KEY_T, VALUE_T> *q = new Node<KEY_T, VALUE_T>;
            q->key = key;
            q->next = nullptr;
            p->next = q;
            return *q;
        } else {
            return *temp;
        }
    }
    Node<KEY_T, VALUE_T> *end() {return &(this->__end);}
    Node<KEY_T, VALUE_T> *find(const KEY_T &key) {
        int hash_code = this->__hash_func(key);
        int index = hash_code % this->__size;
        Node<KEY_T, VALUE_T> *p = this->__data[index].next;
        while (p != nullptr && p->key != key) {p = p->next;}
        if (p != nullptr && p->key == key) {
            return p;
        } else {
            return this->end();
        }
    }
private :
    int __size;
    Node<KEY_T, VALUE_T> *__data;
    HashFunc_T __hash_func;
    Node<KEY_T, VALUE_T> __end;
};

int main() {
    HashTable<string, int> ht;
    ht["sgwx"] = 1;
    ht["sadafd"];
    cout << ht.find("sadafd") << endl;
    return 0;
}

