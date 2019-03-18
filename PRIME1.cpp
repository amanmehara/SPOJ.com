#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <utility>
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

std::vector<std::int64_t> primes(std::int64_t begin, std::int64_t end, std::vector<std::int64_t> primes) {
    std::vector<bool> is_prime(end - begin + 1, true);    
    if(begin == 1) {
        is_prime[0] = false;
    }
    for (size_t i = 0; i < primes.size(); i++) {
        if(primes[i] * primes[i] > end) {
            break;
        }
        std::int64_t mod = begin % primes[i];
        size_t j = (mod == 0) ? begin : begin - mod + primes[i];
        if (j <= primes[i]) {
            j += primes[i];
        }
        while (j <= end) {
            is_prime[j - begin] = false;
            j += primes[i];
        }
    }
    primes.clear();
    for (size_t i = 0; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            primes.push_back(i + begin);
        }
    }
    return primes;
}

int main() {
    int number;
    std::cin >> number;
    std::vector<std::pair<std::int64_t, std::int64_t>> inputs;
    std::int64_t max = 1;
    while (number--) {
        std::int64_t begin, end;
        std::cin >> begin >> end;
        inputs.push_back(std::make_pair(begin, end));
        max = std::max(max, end);
    }
    auto primes_ = sieve_of_eratosthenes(std::sqrt(max));
    for(auto range: inputs) {
        for (std::int64_t prime : primes(range.first, range.second, primes_)) {
            std::cout << prime << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
