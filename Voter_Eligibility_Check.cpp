#include <iostream>
#include <string>
#include <sstream>

int main() {
    int age;
    std::string input;

    while (true) {
        std::cout << "Enter your age: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> age && ss.eof()) {
            break;
        }

        std::cout << "Invalid age entered. Please enter a valid integer age." << std::endl;
    }

    if (18 <= age && age <= 120) {
        std::cout << "Congratulations!" << std::endl;
        std::cout << "You are eligible to vote." << std::endl;
    } else if (12 <= age && age < 18) {
        std::cout << "You are not yet eligible to vote." << std::endl;
        std::cout << "Enjoy your teenage years!" << std::endl;
    } else if (0 <= age && age < 12) {
        std::cout << "You are too young to vote." << std::endl;
        std::cout << "Make the most of your childhood!" << std::endl;
    } else if (age < 0) {
        std::cout << "Invalid age entered." << std::endl;
        std::cout << "Please enter a positive value." << std::endl;
    } else {
        std::cout << "You have surpassed the maximum voting age." << std::endl;
        std::cout << "Thank you for your contribution to society!" << std::endl;
    }

    return 0;
}


// -------------------------------END---------------------------------

// The program above is very Dynamic while the program below is Static

// ------------------------------START--------------------------------


#include<stdio.h>

int main()
{
    int age;

    // Prompt the user to enter their age
    printf("Enter your age: ");
    scanf("%d", &age);

    // Check if the age is within a valid range for voting
    if (age >= 18 && age <= 120) // Considering the maximum human lifespan as 120 years
    {
        printf("Congratulations!\n");
        printf("You are eligible to vote.\n");
    }
    else if (age >= 12 && age < 18)
    {
        printf("You are not yet eligible to vote.\n");
        printf("Enjoy your teenage years!\n");
    }
    else if (age >= 0 && age < 12)
    {
        printf("You are too young to vote.\n");
        printf("Make the most of your childhood!\n");
    }
    else if (age < 0)
    {
        printf("Invalid age entered.\n");
        printf("Please enter a positive value.\n");
    }
    else
    {
        printf("You have surpassed the maximum voting age.\n");
        printf("Thank you for your contribution to society!\n");
    }

    return 0;
}
