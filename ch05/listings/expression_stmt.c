#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Expression Statements ===\n\n");

    // Simple expressions as statements
    printf("Simple expression statements:\n");
    int x = 5; // Assignment expression statement
    x + 3;     // Expression statement (does nothing useful)
    x = x + 1; // Assignment expression statement
    printf("x = %d\n\n", x);

    // Function calls as expression statements
    printf("Function call expression statements:\n");
    printf("Hello, world!\n"); // Function call statement

    // Side effects
    printf("\nExpression statements with side effects:\n");
    int a = 10;
    printf("a = %d\n", a);
    a++; // Post-increment statement
    printf("After a++: a = %d\n", a);
    ++a; // Pre-increment statement
    printf("After ++a: a = %d\n\n", a);

    // Multiple expressions (discouraged style)
    printf("Multiple side effects in one statement:\n");
    int b = 5, c = 10;
    b = c = (c = c + 1, b + c); // Complex but legal
    printf("b = %d, c = %d\n\n", b, c);

    // Null statement
    printf("Null statement (just a semicolon):\n");
    ; // Null statement - does nothing
    printf("A null statement was executed (nothing happened)\n");

    return EXIT_SUCCESS;
}
