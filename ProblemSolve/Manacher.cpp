/*************************************************************************
	> File Name: Manacher
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月15日 星期五 15时34分23秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int Manacher(string s) {
    string s0 = "$#";
    for (int i = 0; i < s.length(); ++i) {
        s0 += s[i];
        s0 += "#";
    }
    cout << s0 << endl;
    int mx = 0, id = 0, maxLen = -1;
    vector<int> p(1000, 0);
    for (int i = 1; i < s0.length(); ++i) {
        if (mx > i) {
            p[i] = min(p[2 * id - i], mx - i);
        } else {
            p[i] = 1;
        }
        while (s0[i + p[i]] == s0[i - p[i]]) {
            p[i]++;
        }
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        maxLen = max(maxLen, p[i] - 1);
    }
    return maxLen;
}

int main() {
    string s;
    cin >> s;
    int x;
    x = Manacher(s);
    cout << x << endl;
    return 0;
}

