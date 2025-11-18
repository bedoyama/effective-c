/*
 * Executables and Program Structure
 *
 * Demonstrates how C programs are structured from source to executable:
 * - Compilation stages
 * - Object files and linking
 * - Entry points and initialization
 * - Program termination
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// PROGRAM INITIALIZATION
// ============================================================================

// Global variables are initialized before main()
int initialized_global = 42;
int uninitialized_global; // Initialized to 0 automatically

// Static variables
static int file_static = 100;
static int file_static_zero; // Also initialized to 0

// ============================================================================
// PROGRAM ENTRY POINTS
// ============================================================================

// Standard main() - most common
// int main(void);
// int main(int argc, char *argv[]);
// int main(int argc, char *argv[], char *envp[]);  // Non-standard but common

// Function called before main (GCC/Clang specific)
__attribute__((constructor)) static void before_main(void)
{
    printf("  This runs BEFORE main()\n");
    printf("  Useful for initialization\n");
}

// Function called after main (GCC/Clang specific)
__attribute__((destructor)) static void after_main(void)
{
    printf("\n  This runs AFTER main()\n");
    printf("  Useful for cleanup\n");
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

void demonstrate_initialization(void)
{
    printf("\nTest 2: Variable Initialization\n");
    printf("  initialized_global = %d (explicit initialization)\n", initialized_global);
    printf("  uninitialized_global = %d (zero-initialized)\n", uninitialized_global);
    printf("  file_static = %d\n", file_static);
    printf("  file_static_zero = %d (zero-initialized)\n", file_static_zero);

    static int static_local = 0;
    static_local++;
    printf("  static_local = %d (persistent across calls)\n", static_local);
}

void demonstrate_storage_classes(void)
{
    printf("\nTest 3: Storage Classes\n");

    // Automatic storage
    int auto_var = 10;
    printf("  auto_var = %d (automatic storage)\n", auto_var);

    // Static storage
    static int static_var = 0;
    static_var++;
    printf("  static_var = %d (static storage, persistent)\n", static_var);

    // Register storage (hint to compiler)
    register int reg_var = 20;
    printf("  reg_var = %d (register hint)\n", reg_var);
}

void demonstrate_program_args(int argc, char *argv[])
{
    printf("\nTest 4: Program Arguments\n");
    printf("  argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("  argv[%d] = \"%s\"\n", i, argv[i]);
    }
}

void demonstrate_environment(char *envp[])
{
    printf("\nTest 5: Environment Variables\n");
    if (envp == NULL)
    {
        printf("  envp not available (use getenv instead)\n");
        const char *path = getenv("PATH");
        const char *home = getenv("HOME");
        printf("  PATH = %s\n", path ? path : "(not set)");
        printf("  HOME = %s\n", home ? home : "(not set)");
    }
    else
    {
        printf("  Environment variables (first 5):\n");
        for (int i = 0; i < 5 && envp[i] != NULL; i++)
        {
            printf("    %s\n", envp[i]);
        }
    }
}

// ============================================================================
// MAIN ENTRY POINT
// ============================================================================

int main(int argc, char *argv[])
{
    printf("\n=== Executables and Program Structure ===\n");

    printf("\nTest 1: Program Entry and Initialization\n");
    printf("  ✓ Constructor ran before main()\n");
    printf("  ✓ Global variables initialized\n");
    printf("  ✓ Static variables initialized to zero\n");
    printf("  ✓ Now in main() function\n");

    demonstrate_initialization();
    demonstrate_storage_classes();
    demonstrate_program_args(argc, argv);
    demonstrate_environment(NULL);

    printf("\n=== Compilation Stages ===\n");
    printf("1. Preprocessing (-E):\n");
    printf("   - Expand macros\n");
    printf("   - Process #include directives\n");
    printf("   - Handle conditional compilation\n");
    printf("   Command: gcc -E file.c -o file.i\n\n");

    printf("2. Compilation (-S):\n");
    printf("   - Parse C code\n");
    printf("   - Generate assembly code\n");
    printf("   - Perform optimizations\n");
    printf("   Command: gcc -S file.c -o file.s\n\n");

    printf("3. Assembly (-c):\n");
    printf("   - Translate assembly to machine code\n");
    printf("   - Create object file (.o)\n");
    printf("   - Contains relocatable code\n");
    printf("   Command: gcc -c file.c -o file.o\n\n");

    printf("4. Linking:\n");
    printf("   - Combine object files\n");
    printf("   - Resolve external references\n");
    printf("   - Link with libraries\n");
    printf("   - Create executable\n");
    printf("   Command: gcc file.o -o program\n\n");

    printf("=== Object Files ===\n");
    printf("Content of .o files:\n");
    printf("  - Machine code (text section)\n");
    printf("  - Initialized data (data section)\n");
    printf("  - Uninitialized data (bss section)\n");
    printf("  - Symbol table (functions, variables)\n");
    printf("  - Relocation information\n");
    printf("  - Debug information (if -g flag)\n\n");

    printf("View object file:\n");
    printf("  nm file.o        # Symbol table\n");
    printf("  objdump -d file.o # Disassembly\n");
    printf("  size file.o      # Section sizes\n\n");

    printf("=== Linking Process ===\n");
    printf("1. Symbol Resolution:\n");
    printf("   - Match function calls to definitions\n");
    printf("   - Match variable references to definitions\n");
    printf("   - Report undefined symbols\n\n");

    printf("2. Relocation:\n");
    printf("   - Assign final addresses\n");
    printf("   - Update references to absolute addresses\n");
    printf("   - Combine sections from multiple files\n\n");

    printf("3. Library Linking:\n");
    printf("   Static: Copy code into executable\n");
    printf("     gcc file.o -o program -l<library>\n");
    printf("   Dynamic: Reference external library\n");
    printf("     gcc file.o -o program -l<library> -Wl,-rpath,<path>\n\n");

    printf("=== Executable Structure ===\n");
    printf("Sections in executable:\n");
    printf("  .text   - Executable code\n");
    printf("  .data   - Initialized global/static data\n");
    printf("  .bss    - Uninitialized global/static data\n");
    printf("  .rodata - Read-only data (string literals, const)\n");
    printf("  .symtab - Symbol table\n");
    printf("  .debug  - Debug information\n\n");

    printf("=== Program Termination ===\n");
    printf("Normal exit:\n");
    printf("  return 0;           from main\n");
    printf("  exit(EXIT_SUCCESS); from anywhere\n");
    printf("  _Exit(0);          immediate exit\n\n");

    printf("Abnormal exit:\n");
    printf("  abort();           terminate with signal\n");
    printf("  assert(condition); terminate if false\n");
    printf("  signal handler     may terminate\n\n");

    printf("Cleanup on exit:\n");
    printf("  - atexit() handlers called\n");
    printf("  - Destructors called (__attribute__((destructor)))\n");
    printf("  - Open files flushed and closed\n");
    printf("  - Temporary files removed\n\n");

    printf("=== Build Commands ===\n");
    printf("Simple build:\n");
    printf("  gcc file.c -o program\n\n");

    printf("Multi-file build:\n");
    printf("  gcc -c file1.c -o file1.o\n");
    printf("  gcc -c file2.c -o file2.o\n");
    printf("  gcc file1.o file2.o -o program\n\n");

    printf("With flags:\n");
    printf("  gcc -Wall -Wextra -std=c11 -O2 -g file.c -o program\n");
    printf("    -Wall -Wextra: Enable warnings\n");
    printf("    -std=c11:      Use C11 standard\n");
    printf("    -O2:           Optimization level 2\n");
    printf("    -g:            Include debug information\n\n");

    printf("=== Program Exit ===\n");
    printf("Exiting with EXIT_SUCCESS...\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Compilation Process:
 *
 *    Source (.c) → Preprocessor → Preprocessed (.i)
 *                  ↓
 *              Compiler
 *                  ↓
 *              Assembly (.s)
 *                  ↓
 *              Assembler
 *                  ↓
 *              Object (.o)
 *                  ↓
 *              Linker  ← Libraries (.a, .so)
 *                  ↓
 *              Executable
 *
 * 2. main() Signatures:
 *
 *    Standard:
 *      int main(void)
 *      int main(int argc, char *argv[])
 *
 *    Common extension:
 *      int main(int argc, char *argv[], char *envp[])
 *
 *    Return value:
 *      0 or EXIT_SUCCESS: Success
 *      Non-zero or EXIT_FAILURE: Failure
 *
 * 3. Program Initialization Order:
 *
 *    1. Load executable into memory
 *    2. Initialize runtime environment
 *    3. Initialize global/static variables
 *    4. Call constructor functions (__attribute__((constructor)))
 *    5. Call main()
 *    6. Call destructor functions (__attribute__((destructor)))
 *    7. Call atexit() handlers
 *    8. Cleanup and exit
 *
 * 4. Storage Classes:
 *
 *    auto (default for locals):
 *      - Automatic storage duration
 *      - Block scope
 *      - Not initialized by default
 *
 *    static:
 *      - Static storage duration (lives entire program)
 *      - File or block scope
 *      - Initialized to zero by default
 *
 *    extern:
 *      - References object in another file
 *      - External linkage
 *
 *    register:
 *      - Hint to store in CPU register
 *      - Cannot take address
 *      - Rarely used, compiler decides anyway
 *
 * 5. Object File Sections:
 *
 *    .text (code segment):
 *      - Executable instructions
 *      - Read-only, shared
 *
 *    .data:
 *      - Initialized global/static variables
 *      - Read-write
 *
 *    .bss (Block Started by Symbol):
 *      - Uninitialized global/static variables
 *      - Initialized to zero at runtime
 *      - Doesn't occupy disk space
 *
 *    .rodata:
 *      - Read-only data
 *      - String literals, const globals
 *
 * 6. Static vs Dynamic Linking:
 *
 *    Static Linking:
 *      - Library code copied into executable
 *      - Larger executable
 *      - No runtime dependencies
 *      - Faster startup
 *
 *    Dynamic Linking:
 *      - References to shared libraries
 *      - Smaller executable
 *      - Requires .so/.dll at runtime
 *      - Saves memory (shared between processes)
 *      - Can update library independently
 *
 * 7. Common Linker Errors:
 *
 *    Undefined reference:
 *      - Function/variable declared but not defined
 *      - Missing object file or library
 *
 *    Multiple definition:
 *      - Same symbol defined in multiple files
 *      - Need to use 'static' or 'extern' properly
 *
 *    Library not found:
 *      - -l flag missing
 *      - Library path not in search path
 *
 * 8. Debugging Executables:
 *
 *    Compile with debug info:
 *      gcc -g file.c -o program
 *
 *    Use debugger:
 *      gdb program
 *      lldb program
 *
 *    View symbols:
 *      nm program
 *      objdump -t program
 *
 *    Disassemble:
 *      objdump -d program
 *      gdb: disassemble main
 *
 * 9. Optimization Levels:
 *
 *    -O0: No optimization (default, best for debugging)
 *    -O1: Basic optimization
 *    -O2: Recommended for production
 *    -O3: Aggressive optimization
 *    -Os: Optimize for size
 *    -Og: Optimize for debugging
 *
 * 10. Build Best Practices:
 *
 *     Development:
 *       gcc -Wall -Wextra -Werror -std=c11 -g -O0 file.c
 *
 *     Production:
 *       gcc -Wall -Wextra -std=c11 -O2 -DNDEBUG file.c
 *
 *     Analysis:
 *       gcc -Wall -Wextra -Wpedantic -std=c11 -fsanitize=address file.c
 */
