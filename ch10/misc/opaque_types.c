/*
 * Opaque Types Demonstration
 *
 * Shows how to use opaque types (incomplete types) to hide implementation details.
 * This is a key technique for encapsulation and information hiding in C.
 *
 * Structure:
 * - This file demonstrates the concept with inline examples
 * - For a real multi-file example, see the queue implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// EXAMPLE 1: BAD - Exposed Structure (NOT Opaque)
// ============================================================================

// BAD: Full structure definition in header (or this demo file)
typedef struct
{
    char name[50];
    int age;
    double salary;
} TransparentEmployee;

void transparent_init(TransparentEmployee *e, const char *name, int age, double salary)
{
    strncpy(e->name, name, sizeof(e->name) - 1);
    e->name[sizeof(e->name) - 1] = '\0';
    e->age = age;
    e->salary = salary;
}

void transparent_print(const TransparentEmployee *e)
{
    printf("  Name: %s, Age: %d, Salary: $%.2f\n", e->name, e->age, e->salary);
}

// ============================================================================
// EXAMPLE 2: GOOD - Opaque Type (Information Hiding)
// ============================================================================

// GOOD: Forward declaration only - implementation hidden
typedef struct opaque_employee OpaqueEmployee;

// In a real program, this would be in the .c file only
struct opaque_employee
{
    char *name; // Using dynamic allocation
    int age;
    double salary;
    int employee_id; // Private field users don't know about
};

// Constructor - allocates and initializes
OpaqueEmployee *opaque_create(const char *name, int age, double salary)
{
    static int next_id = 1000;

    OpaqueEmployee *e = malloc(sizeof(OpaqueEmployee));
    if (e == NULL)
    {
        return NULL;
    }

    e->name = malloc(strlen(name) + 1);
    if (e->name == NULL)
    {
        free(e);
        return NULL;
    }

    strcpy(e->name, name);
    e->age = age;
    e->salary = salary;
    e->employee_id = next_id++;

    return e;
}

// Destructor - frees memory
void opaque_destroy(OpaqueEmployee *e)
{
    if (e != NULL)
    {
        free(e->name);
        free(e);
    }
}

// Getters - controlled access to fields
const char *opaque_get_name(const OpaqueEmployee *e)
{
    return (e != NULL) ? e->name : NULL;
}

int opaque_get_age(const OpaqueEmployee *e)
{
    return (e != NULL) ? e->age : 0;
}

double opaque_get_salary(const OpaqueEmployee *e)
{
    return (e != NULL) ? e->salary : 0.0;
}

int opaque_get_id(const OpaqueEmployee *e)
{
    return (e != NULL) ? e->employee_id : 0;
}

// Setters - controlled modification
void opaque_set_age(OpaqueEmployee *e, int age)
{
    if (e != NULL && age >= 0)
    {
        e->age = age;
    }
}

void opaque_set_salary(OpaqueEmployee *e, double salary)
{
    if (e != NULL && salary >= 0.0)
    {
        e->salary = salary;
    }
}

// Business logic function
void opaque_give_raise(OpaqueEmployee *e, double percentage)
{
    if (e != NULL && percentage > 0.0)
    {
        e->salary *= (1.0 + percentage / 100.0);
    }
}

void opaque_print(const OpaqueEmployee *e)
{
    if (e != NULL)
    {
        printf("  [#%d] %s, Age: %d, Salary: $%.2f\n",
               e->employee_id, e->name, e->age, e->salary);
    }
}

// ============================================================================
// EXAMPLE 3: Handle-Based Opaque Type (Extra Layer of Indirection)
// ============================================================================

// Handle type - just an integer ID
typedef int EmployeeHandle;

#define MAX_EMPLOYEES 100
#define INVALID_HANDLE -1

// Internal storage (would be in .c file)
static struct
{
    char name[50];
    int age;
    double salary;
    int in_use;
} employee_pool[MAX_EMPLOYEES];

static int next_handle = 0;

EmployeeHandle handle_create(const char *name, int age, double salary)
{
    // Find free slot
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        int idx = (next_handle + i) % MAX_EMPLOYEES;
        if (!employee_pool[idx].in_use)
        {
            strncpy(employee_pool[idx].name, name, sizeof(employee_pool[idx].name) - 1);
            employee_pool[idx].name[sizeof(employee_pool[idx].name) - 1] = '\0';
            employee_pool[idx].age = age;
            employee_pool[idx].salary = salary;
            employee_pool[idx].in_use = 1;
            next_handle = (idx + 1) % MAX_EMPLOYEES;
            return idx;
        }
    }
    return INVALID_HANDLE;
}

void handle_destroy(EmployeeHandle handle)
{
    if (handle >= 0 && handle < MAX_EMPLOYEES)
    {
        employee_pool[handle].in_use = 0;
    }
}

const char *handle_get_name(EmployeeHandle handle)
{
    if (handle >= 0 && handle < MAX_EMPLOYEES && employee_pool[handle].in_use)
    {
        return employee_pool[handle].name;
    }
    return NULL;
}

int handle_get_age(EmployeeHandle handle)
{
    if (handle >= 0 && handle < MAX_EMPLOYEES && employee_pool[handle].in_use)
    {
        return employee_pool[handle].age;
    }
    return 0;
}

void handle_print(EmployeeHandle handle)
{
    if (handle >= 0 && handle < MAX_EMPLOYEES && employee_pool[handle].in_use)
    {
        printf("  [Handle %d] %s, Age: %d, Salary: $%.2f\n",
               handle,
               employee_pool[handle].name,
               employee_pool[handle].age,
               employee_pool[handle].salary);
    }
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main(void)
{
    printf("=== Opaque Types Demonstration ===\n\n");

    // ========================================================================
    // Test 1: Transparent Type (BAD)
    // ========================================================================
    printf("Test 1: Transparent Type (NOT opaque)\n");
    TransparentEmployee te;
    transparent_init(&te, "Alice", 30, 75000.0);
    transparent_print(&te);

    printf("  Problem: Users can access internals directly\n");
    te.salary = -1000.0; // BAD: No validation, breaks invariants
    printf("  After direct modification: ");
    transparent_print(&te);

    printf("  ✗ Implementation is exposed\n");
    printf("  ✗ Can't change internal structure without breaking users\n");
    printf("  ✗ No encapsulation or data validation\n\n");

    // ========================================================================
    // Test 2: Opaque Type (GOOD)
    // ========================================================================
    printf("Test 2: Opaque Type (pointer-based)\n");
    OpaqueEmployee *oe = opaque_create("Bob", 35, 80000.0);
    if (oe == NULL)
    {
        fprintf(stderr, "Failed to create opaque employee\n");
        return EXIT_FAILURE;
    }

    opaque_print(oe);
    printf("  ID: %d (private field, only accessible via getter)\n", opaque_get_id(oe));

    printf("  Attempting to give 10%% raise...\n");
    opaque_give_raise(oe, 10.0);
    opaque_print(oe);

    printf("  Attempting to set negative salary (will be rejected)...\n");
    opaque_set_salary(oe, -5000.0); // Validation prevents bad data
    opaque_print(oe);

    printf("  ✓ Implementation is hidden\n");
    printf("  ✓ Can change internals without breaking users\n");
    printf("  ✓ Data validation enforced\n");
    printf("  ✓ Memory management controlled\n");

    opaque_destroy(oe);
    printf("  ✓ Properly cleaned up\n\n");

    // ========================================================================
    // Test 3: Handle-Based Opaque Type
    // ========================================================================
    printf("Test 3: Handle-Based Opaque Type\n");
    EmployeeHandle h1 = handle_create("Charlie", 28, 65000.0);
    EmployeeHandle h2 = handle_create("Diana", 32, 72000.0);

    if (h1 != INVALID_HANDLE && h2 != INVALID_HANDLE)
    {
        handle_print(h1);
        handle_print(h2);

        printf("  ✓ Handles are just integers\n");
        printf("  ✓ No pointer dereferencing by users\n");
        printf("  ✓ Can invalidate handles easily\n");
        printf("  ✓ Can relocate data without breaking users\n");

        handle_destroy(h1);
        handle_destroy(h2);
        printf("  ✓ Handles released\n");
    }
    printf("\n");

    // ========================================================================
    // Summary
    // ========================================================================
    printf("=== Opaque Types Summary ===\n\n");

    printf("Three Approaches:\n\n");

    printf("1. Transparent Type (BAD):\n");
    printf("   typedef struct { int x; int y; } Point;\n");
    printf("   ✗ Users can access fields directly\n");
    printf("   ✗ Can't change implementation\n");
    printf("   ✗ No data validation\n\n");

    printf("2. Pointer-Based Opaque (GOOD):\n");
    printf("   typedef struct point Point;  // Forward declaration\n");
    printf("   Point *point_create(int x, int y);\n");
    printf("   ✓ Implementation hidden in .c file\n");
    printf("   ✓ Controlled access via functions\n");
    printf("   ✓ Can change internals freely\n");
    printf("   ✓ Most common approach\n\n");

    printf("3. Handle-Based Opaque:\n");
    printf("   typedef int ResourceHandle;\n");
    printf("   ResourceHandle resource_create(...);\n");
    printf("   ✓ No pointers exposed\n");
    printf("   ✓ Can relocate data\n");
    printf("   ✓ Easy to serialize\n");
    printf("   ✓ Used in game engines, graphics APIs\n\n");

    printf("=== Benefits of Opaque Types ===\n");
    printf("1. Information Hiding: Implementation details are private\n");
    printf("2. Encapsulation: Data and behavior bundled together\n");
    printf("3. Flexibility: Can change implementation without breaking API\n");
    printf("4. Validation: All access goes through controlled functions\n");
    printf("5. Binary Compatibility: Can update library without recompiling users\n");
    printf("6. Testing: Can mock implementations easily\n\n");

    printf("=== When to Use Opaque Types ===\n");
    printf("✓ Library APIs (maximize flexibility)\n");
    printf("✓ Complex data structures (hide complexity)\n");
    printf("✓ Resource management (control lifecycle)\n");
    printf("✓ Multi-module programs (reduce coupling)\n");
    printf("✗ Simple POD types (unnecessary overhead)\n");
    printf("✗ Performance-critical inner loops (may prefer direct access)\n\n");

    printf("=== Real-World Examples ===\n");
    printf("FILE *        - Standard C library (fopen, fclose)\n");
    printf("DIR *         - POSIX directory operations\n");
    printf("pthread_t     - POSIX threads\n");
    printf("WINDOW *      - ncurses library\n");
    printf("sqlite3 *     - SQLite database\n");
    printf("SSL *         - OpenSSL library\n\n");

    printf("=== File Organization Pattern ===\n\n");

    printf("// point.h (Public Interface)\n");
    printf("#ifndef POINT_H\n");
    printf("#define POINT_H\n");
    printf("\n");
    printf("typedef struct point Point;  // Forward declaration (opaque)\n");
    printf("\n");
    printf("Point *point_create(int x, int y);\n");
    printf("void point_destroy(Point *p);\n");
    printf("int point_get_x(const Point *p);\n");
    printf("int point_get_y(const Point *p);\n");
    printf("void point_set_x(Point *p, int x);\n");
    printf("void point_set_y(Point *p, int y);\n");
    printf("\n");
    printf("#endif\n\n");

    printf("// point.c (Implementation)\n");
    printf("#include \"point.h\"\n");
    printf("#include <stdlib.h>\n");
    printf("\n");
    printf("struct point {  // Full definition (private)\n");
    printf("    int x;\n");
    printf("    int y;\n");
    printf("};\n");
    printf("\n");
    printf("Point *point_create(int x, int y) {\n");
    printf("    Point *p = malloc(sizeof(Point));\n");
    printf("    if (p) { p->x = x; p->y = y; }\n");
    printf("    return p;\n");
    printf("}\n");
    printf("// ... rest of implementation ...\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. What is an Opaque Type?
 *    - A type whose implementation is hidden from users
 *    - Users only see a forward declaration (incomplete type)
 *    - Full definition is in the implementation file
 *    - Forces users to interact through provided functions
 *
 * 2. How to Create Opaque Types:
 *
 *    Header file (public):
 *      typedef struct mytype MyType;  // Incomplete type
 *      MyType *mytype_create(void);
 *      void mytype_destroy(MyType *obj);
 *
 *    Implementation file (private):
 *      struct mytype {  // Complete definition
 *          int private_field;
 *          // ...
 *      };
 *
 * 3. Advantages:
 *    - Implementation can change without recompiling users
 *    - Fields can be added/removed/reordered freely
 *    - Binary compatibility across versions
 *    - Forces good API design
 *    - Prevents misuse of internal fields
 *
 * 4. Disadvantages:
 *    - Requires dynamic allocation (usually)
 *    - More function calls (small overhead)
 *    - Can't allocate on stack by user
 *    - Can't embed in other structures easily
 *
 * 5. Pointer-Based vs Handle-Based:
 *
 *    Pointer-Based:
 *      - typedef struct foo Foo;
 *      - Users get Foo *
 *      - Direct memory access (internally)
 *      - Most common
 *
 *    Handle-Based:
 *      - typedef int FooHandle;
 *      - Users get integer
 *      - Indirect lookup in table
 *      - Extra flexibility (can relocate, serialize)
 *
 * 6. Common Patterns:
 *
 *    Constructor/Destructor:
 *      Type *type_create(...);
 *      void type_destroy(Type *obj);
 *
 *    Getters/Setters:
 *      int type_get_field(const Type *obj);
 *      void type_set_field(Type *obj, int value);
 *
 *    Operations:
 *      void type_do_something(Type *obj, ...);
 *
 * 7. Memory Management:
 *    - Constructor allocates with malloc
 *    - Destructor frees with free
 *    - Clear ownership: caller owns returned pointer
 *    - Document who's responsible for freeing
 *
 * 8. Error Handling:
 *    - Return NULL on allocation failure
 *    - Check for NULL in all functions
 *    - Provide type_is_valid() if needed
 *
 * 9. Const Correctness:
 *    - Use const for read-only operations
 *    - const Type *obj for getters
 *    - Type *obj for setters and mutating operations
 *
 * 10. Testing Opaque Types:
 *
 *     Can create test-only functions in .c file:
 *
 *     #ifdef TESTING
 *     void type_test_access_internals(Type *obj) {
 *         // Direct access for testing
 *     }
 *     #endif
 *
 *     Or create test harness that includes .c file directly
 *
 * 11. Incomplete Types in C:
 *
 *     Forward declaration creates incomplete type:
 *       struct foo;  // Incomplete
 *
 *     Can't:
 *       - Declare variables of this type
 *       - Access members
 *       - Use sizeof
 *
 *     Can:
 *       - Declare pointers to it
 *       - Use in function parameters/return types
 *       - Use in typedef
 *
 * 12. Real-World Example - FILE *:
 *
 *     FILE is defined in stdio.h as opaque:
 *       typedef struct _IO_FILE FILE;  // Forward declaration
 *
 *     Users can't access FILE members, must use:
 *       fopen, fclose, fread, fwrite, etc.
 *
 *     Implementation is in libc and can vary by platform
 */
