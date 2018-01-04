/*************************************************************************
	> File Name: findTheKthNum.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月15日 星期五 17时02分36秒
 ************************************************************************/

#include<iostream>
#include<climits>
using std::cin;
using std::cout;
using std::endl;

#define MAX_N 1000

int n, k, arr[MAX_N + 5];

bool find(int x) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] <= x) count++;
    }
    return count >= k;
}

int ans() {
    int head = 0, tail = INT_MAX, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (find(mid)) {
            tail = mid;
        } else {
            head = mid + 1;
        }
    }
    return head;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << ans() << endl;
    return 0;
}

