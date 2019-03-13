#include <iostream>

int main() {
    int number;
    while (true) {
        std::cin >> number;
        if (number == 42) {
            break;
        }
        std::cout << number << std::endl;
    }
    return 0;
}
