/*************************************************************************
	> File Name: longestSubstring.cpp
	> Author: 上官文雄
	> Mail: sgwx1996@163.com
	> Created Time: 2017年09月17日 星期日 00时24分04秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<climits>
#include<algorithm>

using namespace std;

int longestSubstring(string s) {
    int exist[256] = {0};
    int i = 0, j = 0;
    int maxLen = 0;
    int len = s.length();
    while (j < len) {   
        if (exist[s[j]]) {
            maxLen = max(maxLen, j - i);
            while(s[i] != s[j]) {
                exist[s[i]] = 0;
                i++;
            }
            i++;
            j++;
        } else {
            exist[s[j]] = 1;
            j++;
        }
    }
    maxLen = max(maxLen, len - i);
    return maxLen;
}

int main() {
    string s;
    while (cin >> s) {
        cout << longestSubstring(s) << endl;
    }
    return 0;
}

