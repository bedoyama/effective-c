/*
 * Linkage in C
 *
 * Demonstrates the three types of linkage in C:
 * - External linkage (visible across translation units)
 * - Internal linkage (visible within single translation unit)
 * - No linkage (local scope only)
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// EXTERNAL LINKAGE
// ============================================================================

// External linkage by default for global variables
int global_counter = 0;

// External linkage for functions by default
void external_function(void)
{
    printf("  This function has external linkage\n");
}

// Explicit external linkage with 'extern' keyword
extern int explicitly_external; // Declaration (defined elsewhere)
int explicitly_external = 100;  // Definition

// ============================================================================
// INTERNAL LINKAGE
// ============================================================================

// Internal linkage with 'static' keyword
static int file_scope_counter = 0;

// Static function - internal linkage
static void internal_function(void)
{
    printf("  This function has internal linkage (private to this file)\n");
}

// Static global variable
static const char *module_name = "linkage_demo";

// ============================================================================
// NO LINKAGE
// ============================================================================

void demonstrate_no_linkage(void)
{
    // Local variables have no linkage
    int local_var = 42;

    // Static local variable has no linkage (but persistent storage)
    static int persistent_counter = 0;
    persistent_counter++;

    printf("  Local var: %d (no linkage)\n", local_var);
    printf("  Static local: %d (no linkage, but persistent)\n", persistent_counter);
}

// ============================================================================
// INLINE FUNCTIONS AND LINKAGE
// ============================================================================

// Inline function with external linkage (C99)
inline void inline_function(void)
{
    printf("  Inline function\n");
}

// Static inline - internal linkage, compiler can inline
static inline int fast_multiply_by_2(int x)
{
    return x << 1;
}

// ============================================================================
// CONST AND LINKAGE
// ============================================================================

// const at file scope has EXTERNAL linkage in C (unlike C++)
const int external_const = 42;

// static const has internal linkage
static const int internal_const = 99;

int main(void)
{
    printf("=== Linkage in C ===\n\n");

    printf("Test 1: External Linkage\n");
    printf("  External linkage means the identifier can be referenced\n");
    printf("  from other translation units (files)\n");
    external_function();
    printf("  global_counter = %d\n", global_counter);
    printf("  explicitly_external = %d\n", explicitly_external);
    printf("  external_const = %d\n", external_const);
    printf("  ✓ These can be used in other .c files with 'extern' declarations\n\n");

    printf("Test 2: Internal Linkage (static)\n");
    printf("  Internal linkage means the identifier is private to\n");
    printf("  this translation unit (file)\n");
    internal_function();
    printf("  file_scope_counter = %d\n", file_scope_counter);
    printf("  module_name = %s\n", module_name);
    printf("  internal_const = %d\n", internal_const);
    printf("  ✓ These CANNOT be accessed from other .c files\n\n");

    printf("Test 3: No Linkage\n");
    printf("  Local variables and function parameters have no linkage\n");
    for (int i = 0; i < 3; i++)
    {
        demonstrate_no_linkage();
    }
    printf("  ✓ Local vars are scoped to their block\n");
    printf("  ✓ Static locals persist but still have no linkage\n\n");

    printf("Test 4: Static vs Extern\n");
    printf("  static: Internal linkage (private to file)\n");
    printf("    - Limits scope\n");
    printf("    - Prevents name conflicts\n");
    printf("    - Enables optimizations\n");
    printf("  extern: External linkage (visible to other files)\n");
    printf("    - Shares across translation units\n");
    printf("    - Used for declarations\n");
    printf("    - One definition, many declarations\n\n");

    printf("Test 5: Inline Functions\n");
    inline_function();
    printf("  fast_multiply_by_2(10) = %d\n", fast_multiply_by_2(10));
    printf("  ✓ Inline functions can have external or internal linkage\n");
    printf("  ✓ static inline is common for utility functions\n\n");

    printf("=== Linkage Rules Summary ===\n\n");

    printf("External Linkage:\n");
    printf("  - Global variables (non-static)\n");
    printf("  - Global functions (non-static)\n");
    printf("  - const variables at file scope (in C)\n");
    printf("  - extern declarations\n");
    printf("  Usage: Sharing across files\n\n");

    printf("Internal Linkage:\n");
    printf("  - static global variables\n");
    printf("  - static functions\n");
    printf("  - static const variables\n");
    printf("  Usage: Private implementation details\n\n");

    printf("No Linkage:\n");
    printf("  - Local variables\n");
    printf("  - Function parameters\n");
    printf("  - static local variables (persistent but not linkable)\n");
    printf("  Usage: Temporary computation\n\n");

    printf("=== Best Practices ===\n");
    printf("1. Use 'static' for private functions and variables\n");
    printf("2. Declare shared items in header with 'extern'\n");
    printf("3. Define shared items once in a .c file\n");
    printf("4. Minimize external linkage (reduces coupling)\n");
    printf("5. Use internal linkage by default, external when needed\n");
    printf("6. Put static functions at top of file or declare them\n");
    printf("7. Use static inline for small utility functions\n\n");

    printf("=== Common Patterns ===\n\n");

    printf("Pattern 1: Module-private helpers\n");
    printf("  // my_module.c\n");
    printf("  static int helper(int x) { return x * 2; }  // Private\n");
    printf("  int public_api(int x) { return helper(x); } // Public\n\n");

    printf("Pattern 2: Sharing across files\n");
    printf("  // globals.h\n");
    printf("  extern int shared_counter;  // Declaration\n");
    printf("  \n");
    printf("  // globals.c\n");
    printf("  int shared_counter = 0;     // Definition\n");
    printf("  \n");
    printf("  // main.c\n");
    printf("  #include \"globals.h\"\n");
    printf("  void foo() { shared_counter++; }  // Use\n\n");

    printf("Pattern 3: File-private state\n");
    printf("  // module.c\n");
    printf("  static int instance_count = 0;  // Private to module\n");
    printf("  \n");
    printf("  void *create() {\n");
    printf("      instance_count++;  // Track instances\n");
    printf("      // ...\n");
    printf("  }\n\n");

    printf("=== Linkage and the One Definition Rule ===\n");
    printf("- Each external identifier must have exactly ONE definition\n");
    printf("- Can have multiple declarations (with extern)\n");
    printf("- Violating this causes linker errors\n");
    printf("- Static items don't participate (each file has own copy)\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Three Types of Linkage:
 *
 *    External Linkage:
 *    - Identifier can be referenced from other translation units
 *    - Default for global variables and functions
 *    - Use 'extern' keyword for declarations in headers
 *
 *    Internal Linkage:
 *    - Identifier is private to its translation unit
 *    - Use 'static' keyword
 *    - Each translation unit gets its own copy
 *
 *    No Linkage:
 *    - Identifier is local to its scope
 *    - Local variables, parameters
 *    - Cannot be referenced from outside scope
 *
 * 2. Translation Unit:
 *    - A source file (.c) plus all its included headers
 *    - The basic unit of compilation
 *    - Each .c file is compiled independently
 *
 * 3. Static Keyword Uses:
 *
 *    At file scope:
 *      static int x;        // Internal linkage (private to file)
 *      static void foo();   // Internal linkage
 *
 *    In function:
 *      static int count;    // Persistent storage, no linkage
 *
 *    In function parameter (obsolete):
 *      void foo(static int x[10]);  // Don't use, deprecated
 *
 * 4. Extern Keyword Uses:
 *
 *    Declaration (no storage):
 *      extern int x;        // Declares x defined elsewhere
 *      extern void foo();   // Function declaration
 *
 *    Definition (with initializer):
 *      extern int x = 10;   // Defines x (extern is redundant)
 *
 * 5. Header Files and Linkage:
 *
 *    Header file pattern:
 *      // mymodule.h
 *      #ifndef MYMODULE_H
 *      #define MYMODULE_H
 *
 *      extern int shared_var;      // Declaration
 *      extern void public_func();  // Declaration
 *
 *      #endif
 *
 *    Implementation file:
 *      // mymodule.c
 *      #include "mymodule.h"
 *
 *      int shared_var = 0;         // Definition
 *      void public_func() { }      // Definition
 *
 *      static int private_var = 0; // Private to this file
 *      static void helper() { }    // Private to this file
 *
 * 6. Inline Functions:
 *
 *    C99 inline rules:
 *    - inline suggests to compiler to inline the function
 *    - External linkage by default
 *    - Definition in header must have inline keyword
 *    - One external definition allowed in one .c file
 *
 *    static inline (recommended):
 *    - Internal linkage
 *    - Each translation unit gets its own copy
 *    - Simpler than external inline
 *    - Commonly used in headers
 *
 * 7. Common Errors:
 *
 *    Multiple definitions:
 *      // file1.c
 *      int x = 10;  // Definition
 *
 *      // file2.c
 *      int x = 20;  // Definition - LINKER ERROR!
 *
 *    Undefined reference:
 *      // file1.c
 *      extern int x;  // Declaration
 *      int main() { return x; }  // ERROR: x not defined anywhere
 *
 *    Accessing static from another file:
 *      // file1.c
 *      static int x = 10;
 *
 *      // file2.c
 *      extern int x;  // Declaration, but x has internal linkage!
 *      // x is not accessible - may compile but won't link
 *
 * 8. Linkage vs Scope vs Storage Duration:
 *
 *    Linkage: How identifier is shared across translation units
 *    Scope: Where identifier is visible in code
 *    Storage Duration: How long object exists
 *
 *    Example:
 *      static int x;  // Internal linkage, file scope, static duration
 *
 *      void foo() {
 *          static int y;  // No linkage, block scope, static duration
 *          int z;         // No linkage, block scope, automatic duration
 *      }
 *
 * 9. C vs C++ Differences:
 *
 *    const at global scope:
 *      C:   External linkage (can be shared)
 *      C++: Internal linkage (private by default)
 *
 *    Recommendation: Use static const in C for consistency
 *
 * 10. Testing Linkage:
 *
 *     Create two files to test:
 *
 *     // test1.c
 *     int global = 1;
 *     static int private = 2;
 *
 *     // test2.c
 *     extern int global;   // OK
 *     extern int private;  // ERROR at link time
 *
 *     Compile: gcc test1.c test2.c
 */
