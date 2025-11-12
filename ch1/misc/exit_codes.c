#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Different return codes
    printf("This program demonstrates exit codes.\n");

    // Simulating different scenarios
    int success = 1; // Change to 0 to simulate failure

    if (success)
    {
        printf("Operation successful!\n");
        return EXIT_SUCCESS; // Returns 0
    }
    else
    {
        fprintf(stderr, "Operation failed!\n");
        return EXIT_FAILURE; // Returns non-zero (usually 1)
    }
}
