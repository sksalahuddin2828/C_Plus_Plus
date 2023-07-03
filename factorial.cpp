#include <iostream>
using namespace std;

int calculateFactorial(int);

int main() {
    int number, result;

    cout << "Enter a non-negative number: ";
    cin >> number;

    result = calculateFactorial(number);
    cout << "Factorial of " << number << " = " << result;

    return 0;
}

int calculateFactorial(int n) {
    if (n > 1) {
        return n * calculateFactorial(n - 1);
    } else {
        return 1;
    }
}


# Answer: /tmp/hLh9qnajaq.o
#         Enter a non-negative number: 6
#         Factorial of 6 = 720
