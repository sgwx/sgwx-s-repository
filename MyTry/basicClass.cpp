/*************************************************************************
> File Name: 5.cpp
> Author: 
> Mail: 
> Created Time: 2017年09月07日 星期四 14时05分27秒
************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <ctime>

using std::string;
using std::scanf;
using std::printf;
using std::set;
using std::iterator;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

#define __DEF_LIST_SIZE 32768    
#define __MAX_LIST_SIZE 33554432

#define OK 1
#define ERROR 0

template<typename T>
class list {
public:
    typedef bool (* _Comper)(const T a, const T b);
    list();
    list(int size);
    ~list();

    int insert(T value, int index);
    int delete_ind(int index);
    int find(T value);
    int get_ind(T value);
    int get_len();
    void expand(int new_size);
    void reverse(int left, int right);

    T get_max(_Comper _comp);
    T get_min(_Comper _comp);
    list<T> split(int index);
    void sort(_Comper _comp);

    template<typename S> list<S> friend operator+ (list<S> a, list<S> b);
    template<typename S> list<S> friend operator- (list<S> a, list<S> b);
    void operator() (int left, int right, const string str, int mordel);

private:
    vector<T> data;
    int size, length;
};

bool cmp(string a, string b) {
    return a < b;
}

bool cmp(int a, int b) {
    return a < b;
}

int main() {
    list<string> a, b, c;
    string d, f;
    for (int i = 0 ; i < 4 ; ++i) {
        cin >> d;
        a.insert(d, i);
    }
    a(0, 4, "->", 1);
    a(0, 4, "->", 0);
    for (int i = 0 ; i < 3 ; ++i) {
        cin >> f;
        b.insert(f, i);
    }
    b(0, 3, "->", 0);
    c = a + b;
    c(0, c.get_len(), "-->", 6);
    c = a - b;
    c(0, c.get_len(), "-->", 1);
    cout << "List C max_value is " << c.get_max(cmp) << endl;
    cout << "List C min_value is " << c.get_min(cmp) << endl;
    c.reverse(0, c.get_len());
    c(0, c.get_len(), "->", 1);
    c.sort(cmp);
    c(0, c.get_len(), "->", 5);
    list<string> e = c.split(3);
    c(0, c.get_len(), "->", 3);
    e(0, e.get_len(), "->", 1);
    return 0;
}

template<typename T>
list<T>::list() {
    this->size = __DEF_LIST_SIZE;
    this->length = 0;
}

template<typename T>
list<T>::list(int size) {
    this->size = size;
    this->length = 0;
}

template<typename T>
list<T>::~list() {
    this->data.clear();
    this->size = 0;
    this->length = 0;
}

template<typename T>
int list<T>::insert(T value, int index) {
    if (this->length == this->size) {
        return ERROR;
    }
    for (int i = this->length ; i > index ; --i) {
        this->data[i] = this->data[i - 1];
    }
    if (index == this->length) {
        this->data.push_back(value);
    } else {
        this->data[index] = value;
    }
    ++(this->length);
    return OK;
}

template<typename T>
int list<T>::delete_ind(int index) {
    if (this->length == 0) {
        return ERROR;
    }
    for (int i = index ; i < this->length - 1 ; ++i) {
        this->data[i] = this->data[i + 1];
    }
    --(this->length);
    return OK;
}

template<typename T>
int list<T>::get_ind(T value) {
    int ret_ind = -1;
    for (int i = 0 ; i < this->length ; ++i) {
        if (value == this->data[i]) {
            ret_ind = i;
            break;
        }
    }
    return ret_ind;
}

template<typename T>
void list<T>::expand(int new_size) {

}

template<typename T>
int list<T>::get_len() {
    return this->length;
}

template<typename T> T list<T>::get_max(_Comper comp) {
    T max_value = this->data[0];
    for (int i = 1 ; i < this->length ; ++i) {
        if (comp(max_value, this->data[i])) {
            max_value = this->data[i];
        }
    }
    return max_value;
}

template<typename T>
T list<T>::get_min(_Comper comp) {
    T min_value = this->data[0];
    for (int i = 1 ; i < this->length ; ++i) {
        if (!comp(min_value, this->data[i])) {
            min_value = this->data[i];
        }
    }
    return min_value;
}

template<typename T>
void list<T>::sort(_Comper comp) {
    std::sort(this->data.begin(), this->data.end(), comp);
}

template<typename T>
void list<T>::reverse(int left, int right) {
    for (int i = left, j = right - 1 ; i < j ; ++i, --j) {
        std::swap(this->data[i], this->data[j]);
    }
}

template<typename T>
list<T> list<T>::split(int index) {
    list<T> ret_list;
    for (int i = index ; i < this->length ; ++i) {
        ret_list.data.push_back(this->data[i]);
        ret_list.length++;
    }
    this->length = index;
    return ret_list;
}

template<typename T>
list<T> operator+ (list<T> a, list<T> b) {
    list<T> c(a.get_len() + b.get_len());
    for (int i = 0 ; i < a.get_len() ; ++i) {
        c.data.push_back(a.data[i]);
        c.length++;
    }
    for (int i = 0 ; i < b.get_len() ; ++i) {
        c.data.push_back(b.data[i]);
        c.length++;
    }
    return c;
}

template<typename T>
list<T> operator- (list<T> a, list<T> b) {
    list<T> c(a.get_len() + b.get_len());
    set<T> st;
    for (int i = 0 ; i < a.get_len() ; ++i) {
        st.insert(a.data[i]);
    }
    for (int i = 0 ; i < b.get_len() ; ++i) {
        st.insert(b.data[i]);
    }
    typename set<T>::iterator iter = st.begin();
    while (iter != st.end()) {
        c.data.push_back(*iter);
        ++c.length;
        ++iter;
    }
    return c;
}

template<typename T>
void list<T>::operator() (int left, int right, const string str, int mordel) {
    srand(time(NULL));
    if (mordel == 0) {
        cout << this->data[left];
        for (int k = left + 1; k < right; ++k) {
            int flag = rand() % 7;
            if (flag == 0) {
                cout << str << "\033[31m\033[1m" <<this->data[k];
            } else if (flag == 1) {
                cout << str << "\033[32m\033[1m" <<this->data[k];
            } else if (flag == 2) {
                cout << str << "\033[33m\033[1m" <<this->data[k];
            } else if (flag == 3) {
                cout << str << "\033[34m\033[1m" <<this->data[k];
            } else if (flag == 4) {
                cout << str << "\033[35m\033[1m" <<this->data[k];
            } else if (flag == 5) {
                cout << str << "\033[36m\033[1m" <<this->data[k];
            } else {
                cout << str << "\033[37m\033[1m" <<this->data[k];
            }
        }
    } else {
        for (int j = left; j < right; ++j) {
            for (int k = left; k <= j; ++k) { 
                int flag = rand() % 7;
                if (k == left) {
                    cout << "\033[31m\033[1m" << this->data[k];
                    continue;
                }
                if (flag == 0) {
                    cout << str << "\033[31m\033[1m" <<this->data[k];
                } else if (flag == 1) {
                    cout << str << "\033[32m\033[1m" <<this->data[k];
                } else if (flag == 2) {
                    cout << str << "\033[33m\033[1m" <<this->data[k];
                } else if (flag == 3) {
                    cout << str << "\033[34m\033[1m" <<this->data[k];
                } else if (flag == 4) {
                    cout << str << "\033[35m\033[1m" <<this->data[k];
                } else if (flag == 5) {
                    cout << str << "\033[36m\033[1m" <<this->data[k];
                } else {
                    cout << str << "\033[37m\033[1m" <<this->data[k];
                }
            }
            usleep(900000);
            system("clear");
            fflush(stdout);
        }
    }
    cout << endl;
    sleep(2);
    return;
}

