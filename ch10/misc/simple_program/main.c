/*
 * Simple Calculator - main.c
 *
 * Main program that uses math and ui modules.
 * Demonstrates structuring a simple multi-file program.
 */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "ui.h"

int main(void)
{
    printf("=== Structuring a Simple Program ===\n");
    printf("This calculator demonstrates:\n");
    printf("  - Multiple source files\n");
    printf("  - Separation of concerns (math, ui, main)\n");
    printf("  - Header files for interfaces\n");
    printf("  - Proper compilation and linking\n");

    show_menu();

    int running = 1;
    while (running)
    {
        char op = get_operation();

        switch (op)
        {
        case '+':
        {
            int a = get_integer("First number: ");
            int b = get_integer("Second number: ");
            int result = add(a, b);
            show_result("addition", result);
            break;
        }

        case '-':
        {
            int a = get_integer("First number: ");
            int b = get_integer("Second number: ");
            int result = subtract(a, b);
            show_result("subtraction", result);
            break;
        }

        case '*':
        {
            int a = get_integer("First number: ");
            int b = get_integer("Second number: ");
            int result = multiply(a, b);
            show_result("multiplication", result);
            break;
        }

        case '/':
        {
            int a = get_integer("Numerator: ");
            int b = get_integer("Denominator: ");
            int error;
            int result = divide(a, b, &error);
            if (error)
            {
                show_error("Division by zero");
            }
            else
            {
                show_result("division", result);
            }
            break;
        }

        case '^':
        {
            int base = get_integer("Base: ");
            int exp = get_integer("Exponent: ");
            int result = power(base, exp);
            show_result("power", result);
            break;
        }

        case '!':
        {
            int n = get_integer("Number: ");
            int result = factorial(n);
            show_result("factorial", result);
            break;
        }

        case 'q':
        case 'Q':
            printf("Goodbye!\n");
            running = 0;
            break;

        default:
            show_error("Invalid operation");
            show_menu();
            break;
        }
    }

    printf("\n=== Build Instructions ===\n");
    printf("Method 1: Compile and link separately\n");
    printf("  gcc -c math.c -o math.o\n");
    printf("  gcc -c ui.c -o ui.o\n");
    printf("  gcc -c main.c -o main.o\n");
    printf("  gcc math.o ui.o main.o -o calculator\n\n");

    printf("Method 2: Compile all at once\n");
    printf("  gcc math.c ui.c main.c -o calculator\n\n");

    printf("Method 3: With flags\n");
    printf("  gcc -Wall -Wextra -std=c11 -O2 math.c ui.c main.c -o calculator\n\n");

    printf("Method 4: Using Makefile (recommended)\n");
    printf("  make\n\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. File Structure:
 *    - math.h / math.c: Mathematical operations
 *    - ui.h / ui.c: User interface functions
 *    - main.c: Program entry point and main logic
 *
 * 2. Why Separate Files:
 *    - Modularity: Each file has specific purpose
 *    - Reusability: Can use math.c in other programs
 *    - Maintainability: Easy to find and fix code
 *    - Parallel Development: Different people can work on different modules
 *    - Faster Compilation: Only recompile changed files
 *
 * 3. Header Files:
 *    - Declare interfaces (what)
 *    - Included by both implementation and users
 *    - Protected by header guards
 *    - No function implementations (usually)
 *
 * 4. Implementation Files:
 *    - Define implementations (how)
 *    - Include own header first
 *    - Can have static helper functions
 *
 * 5. Compilation Process:
 *
 *    math.c → [Compiler] → math.o
 *    ui.c   → [Compiler] → ui.o
 *    main.c → [Compiler] → main.o
 *
 *    math.o + ui.o + main.o → [Linker] → calculator
 *
 * 6. Dependencies:
 *
 *    main.c depends on:
 *      - math.h (for math operations)
 *      - ui.h (for user interface)
 *
 *    math.c depends on:
 *      - math.h (its own interface)
 *
 *    ui.c depends on:
 *      - ui.h (its own interface)
 *
 * 7. Makefile Example:
 *
 *    CC = gcc
 *    CFLAGS = -Wall -Wextra -std=c11 -O2
 *
 *    calculator: math.o ui.o main.o
 *        $(CC) $^ -o $@
 *
 *    math.o: math.c math.h
 *        $(CC) $(CFLAGS) -c math.c
 *
 *    ui.o: ui.c ui.h
 *        $(CC) $(CFLAGS) -c ui.c
 *
 *    main.o: main.c math.h ui.h
 *        $(CC) $(CFLAGS) -c main.c
 *
 *    clean:
 *        rm -f *.o calculator
 *
 * 8. Benefits of This Structure:
 *    - Clear separation of concerns
 *    - Easy to test individual modules
 *    - Can swap implementations (e.g., different UI)
 *    - Scales to larger programs
 *    - Standard C project organization
 */
