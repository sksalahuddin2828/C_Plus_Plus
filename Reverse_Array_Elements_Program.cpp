#include <iostream>
#include <vector>

int main() {
    int number;
    std::cout << "Please enter the total number you want to enter: ";
    std::cin >> number;

    std::vector<int> array(number);
    for (int i = 0; i < number; i++) {
        std::cout << "Enter the element " << (i + 1) << ": ";
        std::cin >> array[i];
    }

    for (int i = 0; i < number / 2; i++) {
        int temp = array[i];
        array[i] = array[number - 1 - i];
        array[number - 1 - i] = temp;
    }

    std::cout << "\nReverse all elements of the array:\n";
    for (int element : array) {
        std::cout << element << std::endl;
    }

    return 0;
}
