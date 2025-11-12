/*
 * Header Guards Demonstration
 *
 * Shows why header guards are essential and how they work.
 * Demonstrates the problem of multiple inclusion and the solution.
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// Example 1: WITHOUT header guards (would cause errors if included twice)
// ============================================================================

// Simulate including a header without guards twice
// This would normally be in separate files, but we show it inline for clarity

// First "inclusion" - defining some declarations
#define BUFFER_SIZE 1024
typedef struct
{
    int id;
    char name[50];
} Person;

// If we tried to include the same definitions again (second inclusion),
// we'd get "redefinition" errors. That's why we need header guards!

// ============================================================================
// Example 2: WITH header guards (safe for multiple inclusion)
// ============================================================================

// --- Simulating myheader.h with header guards ---
#ifndef MYHEADER_H
#define MYHEADER_H

#define MAX_USERS 100

typedef struct
{
    int user_id;
    char username[32];
} User;

void print_user(const User *u);

#endif /* MYHEADER_H */

// --- Second "inclusion" of the same header ---
// The preprocessor sees MYHEADER_H is already defined, so it skips this block
#ifndef MYHEADER_H
#define MYHEADER_H

#define MAX_USERS 100

typedef struct
{
    int user_id;
    char username[32];
} User;

void print_user(const User *u);

#endif /* MYHEADER_H */

// ============================================================================
// Implementation
// ============================================================================

void print_user(const User *u)
{
    if (u)
    {
        printf("  User ID: %d, Username: %s\n", u->user_id, u->username);
    }
}

int main(void)
{
    printf("=== Header Guards Demonstration ===\n\n");

    printf("Test 1: Why we need header guards\n");
    printf("  Without guards: Multiple inclusion causes redefinition errors\n");
    printf("  With guards: Safe to include the same header multiple times\n");
    printf("  ✓ Header guards prevent duplicate definitions\n\n");

    printf("Test 2: Header guard pattern\n");
    printf("  Step 1: #ifndef HEADER_NAME_H   // Check if not defined\n");
    printf("  Step 2: #define HEADER_NAME_H   // Define the guard\n");
    printf("  Step 3: ... header contents ... // Actual declarations\n");
    printf("  Step 4: #endif                  // Close the guard\n\n");

    printf("Test 3: Naming conventions\n");
    printf("  myheader.h    → MYHEADER_H\n");
    printf("  math_utils.h  → MATH_UTILS_H\n");
    printf("  vector.h      → VECTOR_H\n");
    printf("  Some projects: PROJECT_MODULE_H or _MYHEADER_H_\n");
    printf("  ✓ Use uppercase with underscores\n\n");

    printf("Test 4: Using the guarded header\n");
    User u1 = {1, "alice"};
    User u2 = {2, "bob"};
    print_user(&u1);
    print_user(&u2);
    printf("  ✓ Functions from guarded header work correctly\n\n");

    printf("Test 5: Alternative - #pragma once\n");
    printf("  Modern compilers support: #pragma once\n");
    printf("  Simpler syntax, but not part of C standard\n");
    printf("  Example:\n");
    printf("    #pragma once\n");
    printf("    // ... header contents ...\n");
    printf("  ✓ Same effect as header guards, compiler-specific\n\n");

    printf("=== Common Scenarios ===\n\n");

    printf("Scenario 1: Indirect multiple inclusion\n");
    printf("  main.c includes → graphics.h and window.h\n");
    printf("  Both graphics.h and window.h include → types.h\n");
    printf("  Result: types.h would be included twice without guards\n");
    printf("  ✓ Header guards prevent the redefinition error\n\n");

    printf("Scenario 2: Circular dependencies\n");
    printf("  a.h needs b.h, and b.h needs a.h (circular)\n");
    printf("  Without guards: Infinite preprocessing loop\n");
    printf("  With guards: Preprocessing stops when already defined\n");
    printf("  ✓ Guards break the circular inclusion cycle\n\n");

    printf("=== Best Practices ===\n");
    printf("1. ALWAYS use header guards in .h files\n");
    printf("2. Use unique guard names (avoid collisions)\n");
    printf("3. Convention: Uppercase filename with _H suffix\n");
    printf("4. Some add project prefix: MYPROJECT_MODULE_H\n");
    printf("5. Add closing comment: #endif /* HEADER_NAME_H */\n");
    printf("6. Never use guards in .c files (not needed)\n");
    printf("7. Consider #pragma once if portability isn't critical\n\n");

    printf("=== Header Guard Template ===\n");
    printf("/* myheader.h */\n");
    printf("#ifndef MYHEADER_H\n");
    printf("#define MYHEADER_H\n");
    printf("\n");
    printf("#include <stdio.h>  /* Standard headers */\n");
    printf("\n");
    printf("/* Constants */\n");
    printf("#define MAX_SIZE 100\n");
    printf("\n");
    printf("/* Type definitions */\n");
    printf("typedef struct {\n");
    printf("    int data;\n");
    printf("} MyStruct;\n");
    printf("\n");
    printf("/* Function declarations */\n");
    printf("void my_function(void);\n");
    printf("\n");
    printf("#endif /* MYHEADER_H */\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Header Guards Purpose:
 *    - Prevent multiple inclusion of the same header file
 *    - Avoid redefinition errors for types, macros, and declarations
 *    - Essential for modular C programming
 *
 * 2. How They Work:
 *    - First inclusion: Guard not defined, content is processed, guard is defined
 *    - Second inclusion: Guard already defined, content is skipped
 *    - Result: Header content is only included once per compilation unit
 *
 * 3. Why Multiple Inclusion Happens:
 *    - Direct: Same .h file included twice in one .c file
 *    - Indirect: Multiple headers include the same common header
 *    - Circular: Two headers include each other
 *
 * 4. Guard Naming:
 *    - Must be unique across the entire project
 *    - Use filename-based names to ensure uniqueness
 *    - Avoid leading underscores (reserved by C standard)
 *
 * 5. #pragma once:
 *    - Non-standard but widely supported
 *    - Simpler syntax: just one line at the top
 *    - May be faster (compiler can skip re-opening file)
 *    - Not guaranteed to work on all compilers
 *
 * 6. Common Mistakes:
 *    - Forgetting #endif
 *    - Using same guard name in different headers
 *    - Putting guards in .c files (unnecessary)
 *    - Misspelling guard name in #ifndef vs #define
 *
 * 7. Testing:
 *    - Try including the same header multiple times
 *    - Should compile without redefinition errors
 *    - Check with: gcc -E file.c to see preprocessed output
 */
