#include <iostream>
using namespace std;

const int grid_size = 9;

// A utility function to print the grid
void printGrid(int grid[grid_size][grid_size]) {
    for (int row = 0; row < grid_size; row++) {
        for (int col = 0; col < grid_size; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Checks whether it will be legal to assign num to the given row, col
bool isSafe(int grid[grid_size][grid_size], int row, int col, int num) {
    // Check if we find the same num in the same row, return false
    for (int checkCol = 0; checkCol < grid_size; checkCol++) {
        if (grid[row][checkCol] == num) {
            return false;
        }
    }

    // Check if we find the same num in the same column, return false
    for (int checkRow = 0; checkRow < grid_size; checkRow++) {
        if (grid[checkRow][col] == num) {
            return false;
        }
    }

    // Check if we find the same num in the particular 3x3 matrix, return false
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int checkRow = 0; checkRow < 3; checkRow++) {
        for (int checkCol = 0; checkCol < 3; checkCol++) {
            if (grid[checkRow + startRow][checkCol + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Takes a partially filled-in grid and attempts to assign values to all unassigned locations
bool solveSudoku(int grid[grid_size][grid_size], int row, int col) {
    // Check if we have reached the last row and column, return true to avoid further backtracking
    if (row == grid_size - 1 && col == grid_size) {
        return true;
    }

    // Check if column value becomes grid_size, move to the next row and column start from 0
    if (col == grid_size) {
        row++;
        col = 0;
    }

    // Check if the current position of the grid already contains a value > 0, iterate for the next column
    if (grid[row][col] > 0) {
        return solveSudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= grid_size; num++) {
        // Check if it is safe to place the num (1-9) in the given row, col
        if (isSafe(grid, row, col, num)) {
            // Assign the num in the current (row, col) position of the grid and assume it is correct
            grid[row][col] = num;

            // Check for the next possibility with the next column
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }

            // If the assumption was wrong, remove the assigned num and go for the next assumption with a different num value
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    // 0 means unassigned cells
    int grid[grid_size][grid_size] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    if (solveSudoku(grid, 0, 0)) {
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
