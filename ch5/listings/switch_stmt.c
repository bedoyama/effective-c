#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Switch Statement ===\n\n");

    // Basic switch
    printf("Basic switch:\n");
    int day = 3;
    printf("Day number: %d\n", day);
    switch (day)
    {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    case 6:
    case 7:
        printf("Weekend\n");
        break;
    default:
        printf("Invalid day\n");
        break;
    }
    printf("\n");

    // Fall-through behavior
    printf("Fall-through (missing break):\n");
    int value = 2;
    printf("Value: %d\n", value);
    printf("Output: ");
    switch (value)
    {
    case 1:
        printf("One ");
    case 2:
        printf("Two "); // Starts here
    case 3:
        printf("Three "); // Falls through
    default:
        printf("Default"); // Falls through
    }
    printf("\n(All cases from 2 onwards executed!)\n\n");

    // Multiple cases for same action
    printf("Multiple cases, same action:\n");
    char grade = 'B';
    printf("Grade: %c\n", grade);
    switch (grade)
    {
    case 'A':
    case 'a':
        printf("Excellent!\n");
        break;
    case 'B':
    case 'b':
        printf("Good job!\n");
        break;
    case 'C':
    case 'c':
        printf("Passed\n");
        break;
    case 'D':
    case 'd':
    case 'F':
    case 'f':
        printf("Failed\n");
        break;
    default:
        printf("Invalid grade\n");
        break;
    }
    printf("\n");

    // Switch with compound statements
    printf("Switch with blocks:\n");
    int choice = 1;
    printf("Choice: %d\n", choice);
    switch (choice)
    {
    case 1:
    {
        int temp = 100;
        printf("Option 1: temp = %d\n", temp);
        break;
    }
    case 2:
    {
        int temp = 200; // Different scope
        printf("Option 2: temp = %d\n", temp);
        break;
    }
    default:
        printf("Default option\n");
        break;
    }

    return EXIT_SUCCESS;
}
