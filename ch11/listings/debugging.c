/*
 * Debugging with GDB/LLDB
 *
 * This file demonstrates common debugging scenarios and techniques.
 * Compile with: gcc -g -O0 -Wall debugging.c -o debugging
 *
 * GDB commands are shown in comments throughout the code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ============================================================================
// Example 1: Basic Debugging Scenarios
// ============================================================================

int buggy_factorial(int n)
{
    // Bug: doesn't handle n=0 correctly, causes infinite recursion for negative
    if (n <= 1)
    {
        return n; // BUG: Should return 1 for n=0
    }
    return n * buggy_factorial(n - 1);
}

int fixed_factorial(int n)
{
    assert(n >= 0); // Precondition
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * fixed_factorial(n - 1);
}

// ============================================================================
// Example 2: Pointer Debugging
// ============================================================================

typedef struct
{
    int id;
    char name[50];
    double salary;
} Employee;

void buggy_employee_init(Employee *emp, int id, const char *name, double salary)
{
    // Bug: doesn't check for NULL pointer
    emp->id = id;
    strncpy(emp->name, name, sizeof(emp->name) - 1);
    emp->name[sizeof(emp->name) - 1] = '\0';
    emp->salary = salary;
}

void fixed_employee_init(Employee *emp, int id, const char *name, double salary)
{
    assert(emp != NULL);
    assert(name != NULL);

    emp->id = id;
    strncpy(emp->name, name, sizeof(emp->name) - 1);
    emp->name[sizeof(emp->name) - 1] = '\0';
    emp->salary = salary;
}

// ============================================================================
// Example 3: Array Bounds Debugging
// ============================================================================

void buggy_array_sum(int *arr, size_t size)
{
    int sum = 0;
    // Bug: off-by-one error
    for (size_t i = 0; i <= size; i++)
    { // Should be i < size
        sum += arr[i];
    }
    printf("Sum: %d\n", sum);
}

void fixed_array_sum(const int *arr, size_t size)
{
    assert(arr != NULL);
    assert(size > 0);

    int sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    printf("Sum: %d\n", sum);
}

// ============================================================================
// Example 4: Memory Leak Debugging
// ============================================================================

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void buggy_list_destroy(Node *head)
{
    // Bug: memory leak - doesn't free all nodes
    if (head != NULL)
    {
        free(head); // Only frees first node
    }
}

void fixed_list_destroy(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

// ============================================================================
// Example 5: Uninitialized Variable
// ============================================================================

int buggy_max_value(const int *arr, size_t size)
{
    int max; // Bug: uninitialized
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int fixed_max_value(const int *arr, size_t size)
{
    assert(arr != NULL);
    assert(size > 0);

    int max = arr[0]; // Initialize with first element
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// ============================================================================
// Example 6: Buffer Overflow
// ============================================================================

void buggy_string_copy(char *dest, const char *src)
{
    // Bug: no bounds checking
    strcpy(dest, src); // Dangerous!
}

void fixed_string_copy(char *dest, size_t dest_size, const char *src)
{
    assert(dest != NULL);
    assert(src != NULL);
    assert(dest_size > 0);

    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

// ============================================================================
// Example 7: Debugging Helper Functions
// ============================================================================

void print_array(const char *label, const int *arr, size_t size)
{
    printf("%s: [", label);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

void print_employee(const char *label, const Employee *emp)
{
    if (emp == NULL)
    {
        printf("%s: NULL\n", label);
        return;
    }
    printf("%s: {id=%d, name=\"%s\", salary=%.2f}\n",
           label, emp->id, emp->name, emp->salary);
}

void print_list(const char *label, const Node *head)
{
    printf("%s: ", label);
    while (head != NULL)
    {
        printf("%d", head->data);
        if (head->next != NULL)
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

// ============================================================================
// Example 8: Conditional Breakpoints
// ============================================================================

void find_bug_in_loop(void)
{
    int problematic_value = -1;

    for (int i = 0; i < 100; i++)
    {
        int value = i * i - 50 * i + 600;

        // This will only trigger for certain values
        if (value < 0)
        {
            problematic_value = value;
            printf("Found negative value: %d at i=%d\n", value, i);
            break;
        }
    }

    printf("Final problematic value: %d\n", problematic_value);
}

// ============================================================================
// Example 9: Core Dump Analysis
// ============================================================================

void cause_segfault_example(void)
{
    // Intentional NULL dereference for core dump demonstration
    // DO NOT call this in production!
    int *ptr = NULL;
    printf("About to dereference NULL pointer...\n");
    // *ptr = 42;  // Uncommenting this causes segfault
    printf("This line won't execute if above is uncommented\n");
}

// ============================================================================
// Main Function
// ============================================================================

int main(void)
{
    printf("=== Debugging Techniques Demo ===\n\n");

    printf("1. Factorial Debugging\n");
    printf("  buggy_factorial(5) would return: (incorrect result)\n");
    printf("  fixed_factorial(5) = %d\n", fixed_factorial(5));
    printf("  fixed_factorial(0) = %d\n\n", fixed_factorial(0));

    printf("2. Pointer Debugging\n");
    Employee emp;
    fixed_employee_init(&emp, 1, "John Doe", 50000.0);
    print_employee("Employee", &emp);
    printf("\n");

    printf("3. Array Bounds\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("  buggy_array_sum would access out of bounds\n");
    printf("  ");
    fixed_array_sum(arr, 5);
    printf("\n");

    printf("4. Memory Management\n");
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    print_list("List", head);
    printf("  buggy_list_destroy would leak memory\n");
    fixed_list_destroy(head);
    printf("  fixed_list_destroy: all nodes freed\n\n");

    printf("5. Uninitialized Variables\n");
    int values[] = {10, 5, 20, 15, 8};
    print_array("Array", values, 5);
    printf("  buggy_max_value would use uninitialized variable\n");
    printf("  fixed_max_value = %d\n\n", fixed_max_value(values, 5));

    printf("6. Buffer Overflow\n");
    char buffer[20];
    fixed_string_copy(buffer, sizeof(buffer), "Safe string");
    printf("  Safely copied: \"%s\"\n\n", buffer);

    printf("7. Loop Debugging\n");
    find_bug_in_loop();
    printf("\n");

    printf("8. Core Dump (safe demonstration)\n");
    cause_segfault_example();
    printf("\n");

    printf("=== GDB/LLDB Quick Reference ===\n\n");

    printf("Starting GDB:\n");
    printf("  gdb ./program              Start GDB with program\n");
    printf("  gdb ./program core         Load core dump\n");
    printf("  gdb --args ./program arg1  Pass arguments\n\n");

    printf("Basic Commands (GDB | LLDB):\n");
    printf("  run (r)                    Start program\n");
    printf("  break main (b main)        Set breakpoint at main\n");
    printf("  break file.c:42            Set breakpoint at line\n");
    printf("  continue (c)               Continue execution\n");
    printf("  next (n)                   Step over (next line)\n");
    printf("  step (s)                   Step into (enter function)\n");
    printf("  finish                     Run until function returns\n");
    printf("  quit (q)                   Exit debugger\n\n");

    printf("Examining Variables:\n");
    printf("  print var (p var)          Print variable value\n");
    printf("  print *ptr                 Dereference pointer\n");
    printf("  print arr[5]               Array element\n");
    printf("  print/x var                Print in hex\n");
    printf("  print/t var                Print in binary\n");
    printf("  display var                Auto-print after each step\n");
    printf("  info locals                Show all local variables\n");
    printf("  info args                  Show function arguments\n\n");

    printf("Examining Memory:\n");
    printf("  x/10x ptr                  Examine 10 words in hex\n");
    printf("  x/10d ptr                  Examine 10 words as decimal\n");
    printf("  x/s ptr                    Examine as string\n");
    printf("  x/10i ptr                  Examine 10 instructions\n\n");

    printf("Breakpoints:\n");
    printf("  break func if x > 10       Conditional breakpoint\n");
    printf("  info breakpoints           List all breakpoints\n");
    printf("  delete 1                   Delete breakpoint #1\n");
    printf("  disable 1                  Disable breakpoint #1\n");
    printf("  enable 1                   Enable breakpoint #1\n");
    printf("  watch var                  Break when var changes\n\n");

    printf("Call Stack:\n");
    printf("  backtrace (bt)             Show call stack\n");
    printf("  frame 2                    Switch to frame #2\n");
    printf("  up                         Move up one frame\n");
    printf("  down                       Move down one frame\n");
    printf("  info frame                 Show current frame info\n\n");

    printf("Advanced Commands:\n");
    printf("  set var x = 10             Change variable value\n");
    printf("  call func(args)            Call function\n");
    printf("  return value               Force function return\n");
    printf("  thread                     Thread commands\n");
    printf("  attach PID                 Attach to running process\n\n");

    printf("=== Common Debugging Workflows ===\n\n");

    printf("1. Segmentation Fault:\n");
    printf("   $ gcc -g -O0 program.c -o program\n");
    printf("   $ gdb ./program\n");
    printf("   (gdb) run\n");
    printf("   [Program crashes]\n");
    printf("   (gdb) backtrace\n");
    printf("   (gdb) frame 2\n");
    printf("   (gdb) print ptr\n");
    printf("   (gdb) print *ptr\n\n");

    printf("2. Infinite Loop:\n");
    printf("   $ gdb ./program\n");
    printf("   (gdb) run\n");
    printf("   [Ctrl+C to interrupt]\n");
    printf("   (gdb) backtrace\n");
    printf("   (gdb) print loop_counter\n");
    printf("   (gdb) break loop_exit_point\n");
    printf("   (gdb) continue\n\n");

    printf("3. Wrong Output:\n");
    printf("   $ gdb ./program\n");
    printf("   (gdb) break suspicious_function\n");
    printf("   (gdb) run\n");
    printf("   (gdb) print input_value\n");
    printf("   (gdb) next [step through]\n");
    printf("   (gdb) print intermediate_result\n");
    printf("   (gdb) continue\n\n");

    printf("4. Memory Corruption:\n");
    printf("   $ gdb ./program\n");
    printf("   (gdb) break main\n");
    printf("   (gdb) run\n");
    printf("   (gdb) watch important_var\n");
    printf("   (gdb) continue\n");
    printf("   [Stops when important_var changes]\n");
    printf("   (gdb) backtrace\n\n");

    printf("5. Core Dump Analysis:\n");
    printf("   $ ulimit -c unlimited        # Enable core dumps\n");
    printf("   $ ./program\n");
    printf("   [Crashes, creates core file]\n");
    printf("   $ gdb ./program core\n");
    printf("   (gdb) backtrace\n");
    printf("   (gdb) frame 0\n");
    printf("   (gdb) info locals\n\n");

    printf("=== Debugging Tips ===\n\n");

    printf("Compilation:\n");
    printf("  • Always use -g flag for debug symbols\n");
    printf("  • Use -O0 to disable optimization\n");
    printf("  • Add -Wall -Wextra for warnings\n");
    printf("  • Consider -fsanitize=address for memory errors\n\n");

    printf("Debugging Strategy:\n");
    printf("  1. Reproduce the bug consistently\n");
    printf("  2. Minimize the test case\n");
    printf("  3. Form a hypothesis about the cause\n");
    printf("  4. Use debugger to test hypothesis\n");
    printf("  5. Fix and verify with tests\n\n");

    printf("Print Debugging:\n");
    printf("  • Use printf for quick checks\n");
    printf("  • Print before/after suspicious operations\n");
    printf("  • Include file/line in debug prints:\n");
    printf("    printf(\"DEBUG %%s:%%d: var=%%d\\n\", __FILE__, __LINE__, var);\n\n");

    printf("Assertions:\n");
    printf("  • Add assertions for invariants\n");
    printf("  • Check function preconditions\n");
    printf("  • Validate data structure consistency\n");
    printf("  • See assertions.c for examples\n\n");

    printf("Tools Integration:\n");
    printf("  • Valgrind: Memory errors and leaks\n");
    printf("  • AddressSanitizer: Fast memory error detection\n");
    printf("  • GDB + Valgrind: gdb --args valgrind ./program\n");
    printf("  • Static analyzers: See static_analysis.c\n");

    return EXIT_SUCCESS;
}

/*
 * DEBUGGING CHECKLIST:
 *
 * [ ] Compile with debug symbols: -g
 * [ ] Disable optimization: -O0
 * [ ] Enable all warnings: -Wall -Wextra
 * [ ] Check for NULL pointers
 * [ ] Verify array bounds
 * [ ] Initialize all variables
 * [ ] Check return values
 * [ ] Free allocated memory
 * [ ] Use assertions for invariants
 * [ ] Add debug print statements
 * [ ] Test edge cases
 * [ ] Use debugger (GDB/LLDB)
 * [ ] Run with sanitizers
 * [ ] Check with Valgrind
 * [ ] Review recent changes
 * [ ] Reproduce consistently
 *
 * COMMON BUG PATTERNS:
 *
 * 1. Null Pointer Dereference:
 *    - Always check pointers before use
 *    - Use assertions: assert(ptr != NULL)
 *
 * 2. Buffer Overflow:
 *    - Use strncpy instead of strcpy
 *    - Always check array bounds
 *    - Use sizeof() for buffer sizes
 *
 * 3. Memory Leaks:
 *    - Every malloc needs a free
 *    - Check all code paths
 *    - Use Valgrind to detect
 *
 * 4. Uninitialized Variables:
 *    - Initialize at declaration
 *    - Compiler warnings: -Wuninitialized
 *    - Compile with -O1 or higher to detect
 *
 * 5. Off-by-One Errors:
 *    - Check loop conditions: < vs <=
 *    - Array access: 0 to size-1
 *    - String termination: buf[size-1] = '\0'
 *
 * 6. Use After Free:
 *    - Set pointers to NULL after free
 *    - Don't access freed memory
 *    - Use Valgrind/ASan to detect
 *
 * 7. Integer Overflow:
 *    - Check before arithmetic operations
 *    - Use wider types if needed
 *    - Compile with -fsanitize=undefined
 *
 * 8. Sign/Unsigned Comparison:
 *    - Warning: -Wsign-compare
 *    - Be careful with size_t
 *    - Cast explicitly if needed
 *
 * 9. Missing Return Value Check:
 *    - Check malloc, fopen, etc.
 *    - Handle errors appropriately
 *    - Warning: -Wunused-result
 *
 * 10. Dangling Pointers:
 *     - Don't return addresses of local variables
 *     - Be careful with pointer lifetimes
 *     - Use static or heap allocation
 */
