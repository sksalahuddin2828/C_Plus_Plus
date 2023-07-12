#include <iostream>
#include <cmath>

int main() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;

    // Find the square root of the number
    double realPart = sqrt(fabs(num));
    double imaginaryPart = sqrt(-num);

    // Display the result
    if (imaginaryPart == 0) {
        std::cout << "The square root of " << num << " is " << std::fixed << realPart << std::endl;
    } else {
        std::cout << "The square root of " << num << " is " << std::fixed << realPart << "+" << imaginaryPart << "i" << std::endl;
    }

    return 0;
}
