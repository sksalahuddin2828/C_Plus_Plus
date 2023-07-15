#include <iostream>
#include <algorithm>

int kaprekar_constant(int n) {
    int count = 0;
    while (n != 6174) {
        count++;
        std::string digits = std::to_string(n);
        digits.insert(0, 4 - digits.length(), '0');
        std::sort(digits.begin(), digits.end());
        int ascending = std::stoi(digits);
        std::reverse(digits.begin(), digits.end());
        int descending = std::stoi(digits);
        n = descending - ascending;
    }
    return count;
}

int main() {
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    int steps = kaprekar_constant(num);
    std::cout << "Number of steps to reach Kaprekar constant: " << steps << std::endl;
    return 0;
}
