#include <iostream>
#include <cmath>

bool is_armstrong_number(int n) {
    int num_digits = 0;
    int temp = n;
    while (temp > 0) {
        temp /= 10;
        num_digits++;
    }
    int sum_of_powers = 0;
    temp = n;
    while (temp > 0) {
        int digit = temp % 10;
        sum_of_powers += pow(digit, num_digits);
        temp /= 10;
    }
    return n == sum_of_powers;
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    if (is_armstrong_number(num)) {
        std::cout << num << " is an Armstrong number." << std::endl;
    } else {
        std::cout << num << " is not an Armstrong number." << std::endl;
    }
    return 0;
}
