/*************************************************************************
	> File Name: 16.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年09月10日 星期日 08时21分49秒
 ************************************************************************/

#include<iostream>
#include<functional>
#include<ctime>
using namespace std;

auto insert_sort = [](int *num, int n) {
    if (n <= 1) return ;
    for (int i = 1; i < n; ++i) {
        if (num[i] < num[0]) {
            swap(num[i], num[0]);
        }
    }
    for (int i = 2; i < n; ++i) {
        int j = i;
        while (num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
};
        
auto my_sort = [](int threthold) {
    function<void(int*, int, int)> quick_sort = [=, &quick_sort](int *num, int left, int right) {
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
            quick_sort(num, x + 1, right);
            right = x - 1;
        }
    };
    return quick_sort;
};

auto sort1 = my_sort(16);

void rand_value(int *num, int n) {
    while (n--) {
        num[n] = rand() % 100000;
    }
    return ;
}

void output(int *num, int n) {
    for (int i = 0; i < n; ++i) {
        if (i % 10 == 0) {
            cout << endl;
        }
        cout << num[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int arr[100];
    rand_value(arr, 100);
    sort1(arr, 0, 99);
    output(arr, 100);
    return 0;
}

