//----------------------------------------------------------------C++ Coding Challenges---------------------------------------------------------

// C++ Coding Challenges on Numbers 
// Write a program in C++ to -

// 1. Convert decimal numbers to octal numbers.
// 2. Reverse an integer.
// 3. Print the Fibonacci series using the recursive method.
// 4. Return the Nth value from the Fibonacci sequence.
// 5. Find the average of numbers (with explanations).
// 6. Convert Celsius to Fahrenheit.

//----------------------------------------------------------------Solution of Problem:----------------------------------------------------------

// 1. Converting Decimal Numbers to Octal Numbers:

#include <iostream>
using namespace std;

int main() {
    int decimal_number = 25;
    int octal_number[100];
    int i = 0;

    while (decimal_number > 0) {
        octal_number[i] = decimal_number % 8;
        decimal_number = decimal_number / 8;
        i++;
    }

    cout << "Octal number: ";

    for (int j = i - 1; j >= 0; j--) {
        cout << octal_number[j];
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

// 2. Reversing an Integer:

