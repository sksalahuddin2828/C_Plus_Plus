#include <iostream>
#include <vector>
#include <algorithm>

int stackSack(int items, const std::vector<int>& weight, const std::vector<int>& value, int number) {
    std::vector<std::vector<int>> knapsack(number + 1, std::vector<int>(items + 1, 0));

    // Build table for knapsack[][] in bottom-up manner
    for (int i = 0; i <= number; i++) {
        for (int j = 0; j <= items; j++) {
            if (i == 0 || j == 0) {
                knapsack[i][j] = 0;
            } else if (weight[i - 1] <= j) {
                knapsack[i][j] = std::max(value[i - 1] + knapsack[i - 1][j - weight[i - 1]], knapsack[i - 1][j]);
            } else {
                knapsack[i][j] = knapsack[i - 1][j];
            }
        }
    }

    return knapsack[number][items];
}

int main() {
    std::vector<int> value = {60, 100, 120};
    std::vector<int> weight = {10, 20, 30};
    int items = 50;
    int number = value.size();

    int result = stackSack(items, weight, value, number);
    std::cout << result << std::endl;

    return 0;
}
