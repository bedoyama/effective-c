#include <stdio.h>
#include <stdlib.h> // For malloc() and free()

int main() {
    // 1. Declaration: An array of 17 pointers to float
    float *afp[17];

    // --- Example 1: Using malloc (dynamic memory) ---

    // 2. Initialization: Allocate memory for a float for afp[0]
    afp[0] = (float*)malloc(sizeof(float));

    // 3. Set the value: Use * to access the memory
    *afp[0] = 9.81f;

    // 4. Get the value: Use * again
    printf("Value at afp[0]: %f\n", *afp[0]); // Prints 9.81
    
    // 5. Clean up the memory you allocated
    free(afp[0]);
    afp[0] = NULL; // Good practice


    // --- Example 2: Pointing to a local variable ---
    
    float pi = 3.14159f;

    // 2. Initialization: Point afp[1] to the 'pi' variable
    afp[1] = &pi;

    // 3. Get the value:
    printf("Value at afp[1]: %f\n", *afp[1]); // Prints 3.14159

    // 4. Set the value (this will also change 'pi'!)
    *afp[1] = 3.5f;

    printf("New value at afp[1]: %f\n", *afp[1]); // Prints 3.5
    printf("Value of 'pi' is now: %f\n", pi);   // Also prints 3.5

    // No 'free' needed here, as 'pi' is on the stack
    
    return 0;
}