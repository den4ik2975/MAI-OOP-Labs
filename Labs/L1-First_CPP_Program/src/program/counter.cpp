#include "../headers/counter.h"

#include <cstdint>

// Helper function to count ones up to n
static int64_t GetOnes(int64_t n) {
    if (n == 0) return 0;
    int64_t power_of_2 = 1;
    int bit_position = 0;
    while ((power_of_2 << 1) <= n) {
        power_of_2 <<= 1;
        bit_position++;
    }
    return (bit_position * power_of_2 / 2) + (n - power_of_2 + 1) +
           GetOnes(n - power_of_2);
}

int64_t CountOnes(int64_t a, int64_t b) {
    if (a == 0) {
        a = 1;
    }
    return GetOnes(b) - GetOnes(a - 1);
}
