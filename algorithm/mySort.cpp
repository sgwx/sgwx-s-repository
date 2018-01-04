/*************************************************************************
> File Name: 20.cpp
> Author: 上官文雄
> Mail: sgwx1996@163.com
> Created Time: 2017年09月10日 星期日 11时42分39秒
************************************************************************/

#include <iostream>
#include <functional>
#include <ctime>
using namespace std;

namespace haizei {
class ostream;
auto insert_sort = [](int *num, int n) {
    if (n <= 1) return ;
    for (int i = 1; i < n; i++) {
        if (num[i] < num[0]) {
            swap(num[i], num[0]);
        }
    }
    for (int i = 2; i < n; i++) {
        int j = i;
        while (num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
};

class my_sort {
public :
    my_sort() : threthold(16) {}
    my_sort(int x) : threthold(x) {}
    void set_threthold(int x) {
        this->threthold = x;
    }
    void operator()(int *num, int n) {
    cout << "sort : " << this->threthold << endl;
    this->__sort(num, 0, n - 1);
    }
friend ostream &operator<<(ostream &out, my_sort &a);
private :
    int threthold;
    void __sort(int *num, int left, int right) {
        while (left < right) {
            if (right - left < threthold) {
                insert_sort(num + left, right - left + 1);
            return ;
        }
        int x, y, z;
        x = left, y = right, z = num[left];
        while (x < y) {
            while (x < y && num[y] >= z) y--;
            if (x < y) num[x++] = num[y];
            while (x < y && num[x] <= z) x++;
            if (x < y) num[y--] = num[x];
        }
        num[x] = z;
        this->__sort(num, x + 1, right);
        right = x - 1;
    }
        return ;
    }
};

class Precision {
    public :
    Precision(int x) : precision(x) {}
    int precision;
};

class ostream {
public :
    ostream() = default;
    ostream &operator <<(const int x) {
        char fmt[15];
        sprintf(fmt, "%%0%dd",this->__precision);
        this->__Print(fmt, x);
        return *this;
    }
    ostream &operator <<(const double x) {
        char fmt[15];
        sprintf(fmt, "%%.%dlf", this->__precision);
        this->__Print(fmt, x);
        return *this;
    }
    ostream &operator <<(const char *str) {
        this->__Print("%s", str);
        return *this;
    }
    ostream &operator <<(const Precision &a) {
        this->__precision = a.precision;
        return *this;
    }
private :
    int __precision;
    template<typename T>
    void __Print(const char *fmt, T &x) {
        printf(fmt, x);
        return ;
    }
};
auto sort = my_sort();
auto cout = ostream();
auto endl = "\n";
ostream &operator<<(ostream &out, my_sort &a) {
    out << "my threthold is : " << a.threthold << endl;
    return out;
}
};

void rand_value(int *num, int n) {
    while (n--) {
        num[n] = rand() % 100;
    }
}

void output(int *num, int n) {
    for (int i = 0; i < n; i++) {
        cout << num[i] << " ";
        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

struct Point {
    int x, y;
};

haizei::ostream &operator<<(haizei::ostream &out, Point &a) {
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

int main() {
    srand(time(0));
    int arr[100];

    haizei::cout << haizei::Precision(13) << 4 << haizei::endl;
    return 0;
}
