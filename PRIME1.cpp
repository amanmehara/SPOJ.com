#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<std::int64_t> sieve_of_eratosthenes(std::int64_t number) {
    std::vector<bool> is_prime(number + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (size_t i = 0; i * i <= number; i++) {
        if (is_prime[i]) {
            for (size_t j = i * i; j <= number; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<std::int64_t> primes;
    for (size_t i = 0; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

std::vector<std::int64_t> primes(std::int64_t begin, std::int64_t end) {
    std::vector<std::int64_t> primes;
    if (begin <= std::sqrt(end) || end <= 100000) {
        primes = sieve_of_eratosthenes(end);
    } else {
        primes = sieve_of_eratosthenes(std::sqrt(end));
        std::vector<bool> is_prime(end - begin + 1, true);
        for (size_t i = 0; i < primes.size(); i++) {
            std::int64_t mod = begin % primes[i];
            for (size_t j = (mod == 0) ? begin : begin - mod + primes[i]; j <= end; j += primes[i]) {
                is_prime[j - begin] = false;
            }
        }
        primes.clear();
        for (size_t i = 0; i < is_prime.size(); i++) {
            if (is_prime[i]) {
                primes.push_back(i + begin);
            }
        }
    }
    return primes;
}

int main() {
    int number;
    std::cin >> number;
    while (number--) {
        std::int64_t begin, end;
        std::cin >> begin >> end;
        for (std::int64_t prime : primes(begin, end)) {
            std::cout << prime << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
