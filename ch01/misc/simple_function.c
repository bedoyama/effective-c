#include <stdio.h>
#include <stdlib.h>

// Function declaration
void greet(void);

int main(void)
{
    printf("Main function starting...\n");

    // Call our function
    greet();

    printf("Main function ending...\n");

    return EXIT_SUCCESS;
}

// Function definition
void greet(void)
{
    printf("  Hello from the greet function!\n");
}
