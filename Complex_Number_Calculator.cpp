#include <iostream>
using namespace std;

class Complex {
public:
    float real;
    float imag;
    
    void set_data() {
        cout << "Enter the real value of the complex number: ";
        cin >> real;
        cout << "Enter the imaginary value of the complex number: ";
        cin >> imag;
    }
    
    void add(float a, float b, float c, float d) {
        real = a + c;
        imag = b + d;
    }
    
    void subtract(float a, float b, float c, float d) {
        real = a - c;
        imag = b - d;
    }
    
    void multiply(float a, float b, float c, float d) {
        real = a * c - b * d;
        imag = a * d + b * c;
    }
    
    void divide(float a, float b, float c, float d) {
        real = (a * c + b * d) / (c * c + d * d);
        imag = (b * c - a * d) / (c * c + d * d);
    }
    
    void get_data() {
        if (imag >= 0) {
            cout << real << "+" << imag << "i" << endl;
        } else {
            cout << real << imag << "i" << endl;
        }
    }
};

int main() {
    Complex x1, x2, addition, subtraction, multiplication, division;
    
    x1.set_data();
    x2.set_data();
    
    cout << "Complex number 1 is:" << endl;
    x1.get_data();
    cout << "Complex number 2 is:" << endl;
    x2.get_data();
    
    int ans = 1;
    while (ans == 1) {
        cout << "Choose the operation to perform:" << endl;
        cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division" << endl;
        int a;
        cin >> a;
        
        if (a == 1) {
            addition.add(x1.real, x1.imag, x2.real, x2.imag);
            cout << "Addition of Complex 1 and Complex 2 is:" << endl;
            addition.get_data();
        } else if (a == 2) {
            subtraction.subtract(x1.real, x1.imag, x2.real, x2.imag);
            cout << "Subtraction of Complex 2 from Complex 1 is:" << endl;
            subtraction.get_data();
        } else if (a == 3) {
            multiplication.multiply(x1.real, x1.imag, x2.real, x2.imag);
            cout << "Multiplication of Complex 1 and Complex 2 is:" << endl;
            multiplication.get_data();
        } else if (a == 4) {
            if (x2.real == 0 && x2.imag == 0) {
                cout << "Can't divide by zero" << endl;
            } else {
                division.divide(x1.real, x1.imag, x2.real, x2.imag);
                cout << "On division of Complex 1 by Complex 2, we get:" << endl;
                division.get_data();
            }
        } else {
            cout << "Invalid option chosen!" << endl;
        }
        
        cout << "Do you want to check more? (1 for yes / 2 for no): ";
        cin >> ans;
        if (ans == 2) {
            break;
        }
    }
    
    cout << "\nThank you" << endl;
    
    return 0;
}
