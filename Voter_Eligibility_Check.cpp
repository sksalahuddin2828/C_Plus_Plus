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
