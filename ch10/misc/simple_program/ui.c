/*
 * Simple Calculator - ui.c
 *
 * Implementation of user interface functions.
 */

#include "ui.h"
#include <stdio.h>

void show_menu(void)
{
    printf("\n=== Simple Calculator ===\n");
    printf("Operations:\n");
    printf("  +  Addition\n");
    printf("  -  Subtraction\n");
    printf("  *  Multiplication\n");
    printf("  /  Division\n");
    printf("  ^  Power\n");
    printf("  !  Factorial\n");
    printf("  q  Quit\n");
}

void show_result(const char *operation, int result)
{
    printf("Result: %s = %d\n", operation, result);
}

void show_error(const char *message)
{
    fprintf(stderr, "Error: %s\n", message);
}

int get_integer(const char *prompt)
{
    int value;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1)
    {
        // Clear input buffer on error
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return 0;
    }
    return value;
}

char get_operation(void)
{
    char op;
    printf("Operation: ");
    scanf(" %c", &op); // Space before %c to skip whitespace
    return op;
}
