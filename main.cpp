#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>



#define AVG_10(func) \
    []() { \
        double total_time = 0; \
        for (int i = 0; i < 10; ++i) { \
            auto start = std::chrono::high_resolution_clock::now(); \
            uint32_t primes = func(10'000'000u); \
            auto end = std::chrono::high_resolution_clock::now(); \
            total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
        } \
        return total_time / 10.0; \
    }()

unsigned int sieve_of_eratosthenes(uint32_t n) {
    std::vector<bool> is_prime((n-1)/2 + 1, true);

    uint_fast32_t primes = (n > 2) ? 1 : 0;
    uint_fast32_t max_check = static_cast<uint_fast32_t>(std::sqrt(n));

    for (uint_fast32_t i = 3; i <= max_check; i += 2) {
        if (is_prime[(i-1)/2]) {
            ++primes;
            for (uint_fast32_t j = i * i; j <= n; j += i * 2) {
                is_prime[(j-1)/2] = false;
            }
        }
    }

    for (uint_fast32_t i = max_check + ((max_check & 1) ? 2 : 1); i <= n; i += 2) {
        if (is_prime[(i-1)/2]) {
            ++primes;
        }
    }
    return primes;
}

int main() {
    std::cout << "Average time taken: " << AVG_10(sieve_of_eratosthenes) << " ms" << std::endl;
    return 0;
}