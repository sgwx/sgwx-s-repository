/*************************************************************************
	> File Name: 7.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月16日 星期四 11时30分32秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_N 40000

int64_t prime1[MAX_N + 5] = {0};
int64_t prime2[MAX_N + 5] = {0};
int64_t num_prime[MAX_N + 5] = {0};

int64_t how_many(int64_t &x, int p) {
    if (x == 1 || p == 1) return 0;
    int ret = 0;
    while (x % p == 0) x /= p, ret++;
    return ret;
}

int64_t how_many_prime(int64_t x, int64_t *p) {
    int many = 1;
    while (x != 1) {
        many *= (how_many(x, p[x]) + 1);
    }
    return many;
}

void init_prime(int64_t *p1, int64_t *p2, int range) {
    for (int i = 2; i <= range; ++i) {
        if (!p1[i]) {p2[++p2[0]] = i, p1[i] = i;}
        for (int j = 1; j <= p2[0] && p2[j] * i <= range; ++j) {
            p1[p2[j] * i] = p2[j];
            if (i % p2[j] == 0) break;
        }
    }
}

int main() {
    init_prime(prime1, prime2, MAX_N);
    for (int64_t i = 1; i <= MAX_N; ++i) {
        num_prime[i] = how_many_prime(i, prime1);
    }
    int n, a;
    std::cin >> n;
    while (n) {
        std::cin >> a;
        n--;
        std::cout << how_many_prime(a, prime1) << std::endl;
    }
    int ret = 0, many1, many2;
    for (int i = 2; i <= MAX_N; i += 2) {
        many1 = num_prime[i / 2] * num_prime[i - 1];
        many2 = num_prime[i / 2] * num_prime[i + 1];
        if (many1 >= 500) {
            ret = (i / 2) * (i - 1);
            break;
        } else if (many2 >= 500) {
            ret = (i / 2) * (i + 1);
            break;
        }
    }
    printf("%d\n", ret);
    return 0;
}

