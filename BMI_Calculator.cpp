#include <iostream>

int main() {
    float height, weight;

    std::cout << "Enter your height in centimeters: ";
    std::cin >> height;

    std::cout << "Enter your weight in Kg: ";
    std::cin >> weight;

    height = height / 100;
    float bmi = weight / (height * height);

    std::cout << "Your Body-Mass index is: " << std::fixed << std::setprecision(2) << bmi << std::endl;

    if (bmi > 0) {
        if (bmi <= 16) {
            std::cout << "You are severely under-weight." << std::endl;
        } else if (bmi <= 18.5) {
            std::cout << "You are under-weight." << std::endl;
        } else if (bmi <= 25) {
            std::cout << "You are Healthy." << std::endl;
        } else if (bmi <= 30) {
            std::cout << "You are overweight." << std::endl;
        } else {
            std::cout << "You are severely overweight." << std::endl;
        }
    } else {
        std::cout << "Please enter valid details." << std::endl;
    }

    return 0;
}
