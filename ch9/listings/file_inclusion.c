#include <stdio.h>
#include <stdlib.h>

// System headers - use angle brackets
#include <string.h>
#include <math.h>

// User headers - use quotes
// #include "myheader.h"

int main(void)
{
    printf("=== File Inclusion ===\n\n");

    printf("Test 1: Using standard library functions\n");
    {
        // From stdio.h
        printf("  printf() from <stdio.h>\n");

        // From string.h
        char str[] = "Hello";
        printf("  strlen() from <string.h>: %zu\n", strlen(str));

        // From math.h
        double result = sqrt(16.0);
        printf("  sqrt() from <math.h>: %.1f\n", result);
    }
    printf("\n");

    printf("Test 2: Include directive forms\n");
    {
        printf("  #include <file.h>  - System/standard headers\n");
        printf("    • Searches system include paths\n");
        printf("    • /usr/include, /usr/local/include, etc.\n");
        printf("\n");

        printf("  #include \"file.h\"  - User/local headers\n");
        printf("    • Searches current directory first\n");
        printf("    • Then searches system paths\n");
        printf("    • Use for your own header files\n");
    }
    printf("\n");

    printf("Test 3: Include guard pattern (in header files)\n");
    {
        printf("  Prevents multiple inclusion:\n");
        printf("\n");
        printf("  #ifndef MYHEADER_H\n");
        printf("  #define MYHEADER_H\n");
        printf("  // Header contents here\n");
        printf("  #endif // MYHEADER_H\n");
    }
    printf("\n");

    printf("Test 4: Common standard headers\n");
    {
        printf("  <stdio.h>      - Standard I/O\n");
        printf("  <stdlib.h>     - General utilities\n");
        printf("  <string.h>     - String handling\n");
        printf("  <math.h>       - Math functions\n");
        printf("  <stdbool.h>    - Boolean type\n");
        printf("  <stdint.h>     - Fixed-width integers\n");
        printf("  <limits.h>     - Implementation limits\n");
        printf("  <time.h>       - Time/date functions\n");
        printf("  <ctype.h>      - Character handling\n");
        printf("  <assert.h>     - Assertions\n");
    }
    printf("\n");

    printf("=== Important Notes ===\n");
    printf("1. #include is a preprocessor directive (not C code)\n");
    printf("2. Literally copies file contents at that point\n");
    printf("3. Use <> for system headers, \"\" for your headers\n");
    printf("4. Always use include guards in header files\n");
    printf("5. Don't include .c files, only .h files\n");
    printf("6. Order matters if headers depend on each other\n");

    return EXIT_SUCCESS;
}
