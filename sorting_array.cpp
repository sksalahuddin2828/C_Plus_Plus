#include <iostream>
#include <algorithm>
using namespace std;

bool areArraysEqual(int array1[], int array2[], int length1, int length2) {
    if (length1 != length2) {
        return false;
    }

    // Sort both arrays
    sort(array1, array1 + length1);
    sort(array2, array2 + length2);

    // Linearly compare elements
    for (int i = 0; i < length1; i++) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }

    // If all elements are the same
    return true;
}

int main() {
    int array1[] = {3, 5, 2, 5, 2};
    int array2[] = {2, 3, 5, 5, 2};
    int length1 = sizeof(array1) / sizeof(array1[0]);
    int length2 = sizeof(array2) / sizeof(array2[0]);

    if (areArraysEqual(array1, array2, length1, length2)) {
        cout << "The arrays are equal" << endl;
    } else {
        cout << "The arrays are not equal" << endl;
    }

    return 0;
}
