/*************************************************************************
	> File Name: findN.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月16日 星期六 15时34分27秒
 ************************************************************************/

#include<iostream>
#include<cmath>
using std::cin;
using std::cout;
using std::endl;

int done(int n) {
    if (n <= 3) {
        return n;
    }
    int sum = 3, digit, count, mod;
    for (int i = 2; i < n; ++i) {
        sum += i * (int)(pow(3, i) - pow(3, i - 1));
        if (sum >= n) {
            if (sum == n) {
                return 3;
            }
            digit = i;
            break;
        }
    }
    int x = sum - (digit * (int)(pow(3, digit) - pow(3, digit - 1)));
    count = (n - x - 1) / digit + 1;
    mod = (n - x - 1) % digit;
    int z = pow(3, digit - 1);
    int ans = (z + count - 1) / (int)pow(3, mod);
    ans %= 3;
    return (ans + 1);
}

int main() {
    int n;
    while (cin >> n) {
        cout << done(n) << endl;
    }
    return 0;
}

