#include <stdio.h>
#include <stdlib.h>

/*
 * This file demonstrates the compilation process phases:
 * 1. Preprocessing
 * 2. Compilation
 * 3. Assembly
 * 4. Linking
 */

#define MESSAGE "Hello from preprocessor!"
#define VALUE 42

int main(void)
{
    printf("=== Compilation Process ===\n\n");

    printf("This program demonstrates what happens during compilation.\n\n");

    // The preprocessor replaces MESSAGE with the string literal
    printf("Preprocessor constant: %s\n", MESSAGE);
    printf("Preprocessor value: %d\n", VALUE);

    printf("\n=== Compilation Phases ===\n\n");

    printf("1. Preprocessing:\n");
    printf("   - Process directives (#include, #define, #ifdef, etc.)\n");
    printf("   - Expand macros\n");
    printf("   - Remove comments\n");
    printf("   - Generate .i file (use: gcc -E file.c)\n\n");

    printf("2. Compilation:\n");
    printf("   - Convert preprocessed C code to assembly\n");
    printf("   - Check syntax and semantics\n");
    printf("   - Optimize code\n");
    printf("   - Generate .s file (use: gcc -S file.c)\n\n");

    printf("3. Assembly:\n");
    printf("   - Convert assembly to machine code\n");
    printf("   - Generate object file (.o)\n");
    printf("   - Use: gcc -c file.c\n\n");

    printf("4. Linking:\n");
    printf("   - Combine object files\n");
    printf("   - Resolve external references\n");
    printf("   - Link with libraries\n");
    printf("   - Generate executable\n\n");

    printf("To see each stage:\n");
    printf("  gcc -E file.c         # Preprocessing only\n");
    printf("  gcc -S file.c         # Stop after compilation\n");
    printf("  gcc -c file.c         # Stop after assembly\n");
    printf("  gcc file.c -o program # Complete process\n");

    return EXIT_SUCCESS;
}
