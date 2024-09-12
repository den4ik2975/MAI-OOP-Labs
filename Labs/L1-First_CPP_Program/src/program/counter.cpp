#include "../headers/counter.h"

#include <iostream>

long long getOnes(long long n) {
    if (n == 0) return 0;
    long long powerOf2 = 1;
    int bitPosition = 0;
    while ((powerOf2 << 1) <= n) {
        powerOf2 <<= 1;
        bitPosition++;
    }
    return (bitPosition * powerOf2 / 2) + (n - powerOf2 + 1) + getOnes(n - powerOf2);
}

long long countOnes(long long a, long long b){
    if (a == 0)
    {
        a = 1;
    }
    long long res = getOnes(b) - getOnes(a - 1);
    return res;
}
