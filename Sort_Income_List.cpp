#include <iostream>

int main() {
    int incomeList[10];

    std::cout << "Enter the income of 10 people:" << std::endl;
    for (int person = 0; person < 10; person++) {
        std::cout << "Enter income: ";
        std::cin >> incomeList[person];
    }

    for (int firstIndex = 0; firstIndex < 9; firstIndex++) {
        int swapCount = 0;
        int minIncome = incomeList[firstIndex];
        int minIndex = firstIndex;

        for (int secondIndex = firstIndex + 1; secondIndex < 10; secondIndex++) {
            if (minIncome > incomeList[secondIndex]) {
                minIncome = incomeList[secondIndex];
                swapCount++;
                minIndex = secondIndex;
            }
        }

        if (swapCount != 0) {
            int temp = incomeList[firstIndex];
            incomeList[firstIndex] = minIncome;
            incomeList[minIndex] = temp;
        }
    }

    std::cout << "Sorted income list:" << std::endl;
    for (int income : incomeList) {
        std::cout << income << std::endl;
    }

    return 0;
}
