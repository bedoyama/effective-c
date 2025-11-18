/*
 * Principles of Componentization
 *
 * Demonstrates key principles for organizing C programs into components:
 * - Separation of interface and implementation
 * - Information hiding and encapsulation
 * - Module cohesion and coupling
 * - API design principles
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// EXAMPLE 1: Poor Componentization (BAD)
// ============================================================================

// BAD: Exposing implementation details
typedef struct
{
    int x;
    int y;
    char name[50];
} BadPoint; // Users can access and modify internal fields directly

void bad_point_init(BadPoint *p, int x, int y)
{
    p->x = x;
    p->y = y;
}

// ============================================================================
// EXAMPLE 2: Good Componentization (GOOD)
// ============================================================================

// GOOD: Opaque type - implementation hidden
typedef struct good_point GoodPoint;

// Forward declarations - implementation in separate file (simulated here)
struct good_point
{
    int x;
    int y;
    char name[50];
};

GoodPoint *good_point_create(int x, int y);
void good_point_destroy(GoodPoint *p);
int good_point_get_x(const GoodPoint *p);
int good_point_get_y(const GoodPoint *p);
void good_point_set_x(GoodPoint *p, int x);
void good_point_set_y(GoodPoint *p, int y);

// Implementations
GoodPoint *good_point_create(int x, int y)
{
    GoodPoint *p = malloc(sizeof(GoodPoint));
    if (p)
    {
        p->x = x;
        p->y = y;
    }
    return p;
}

void good_point_destroy(GoodPoint *p)
{
    free(p);
}

int good_point_get_x(const GoodPoint *p)
{
    return p ? p->x : 0;
}

int good_point_get_y(const GoodPoint *p)
{
    return p ? p->y : 0;
}

void good_point_set_x(GoodPoint *p, int x)
{
    if (p)
        p->x = x;
}

void good_point_set_y(GoodPoint *p, int y)
{
    if (p)
        p->y = y;
}

// ============================================================================
// EXAMPLE 3: Module Organization
// ============================================================================

// Recommended file structure for a component:
//
// mymodule.h (Public Interface):
// - #ifndef guards
// - #include dependencies
// - Public type definitions (often opaque)
// - Public function declarations
// - Public constants/macros
//
// mymodule.c (Implementation):
// - #include "mymodule.h"
// - Private types and structures
// - Static (private) helper functions
// - Public function implementations

int main(void)
{
    printf("=== Principles of Componentization ===\n\n");

    printf("Principle 1: Separation of Interface and Implementation\n");
    printf("  Interface (.h file):\n");
    printf("    - What the module does (declarations)\n");
    printf("    - Public API visible to users\n");
    printf("    - Type definitions and constants\n");
    printf("  Implementation (.c file):\n");
    printf("    - How it's done (definitions)\n");
    printf("    - Private helper functions\n");
    printf("    - Internal data structures\n");
    printf("  ✓ Users depend only on interface, not implementation\n\n");

    printf("Principle 2: Information Hiding\n");
    printf("  BAD Example:\n");
    BadPoint bp;
    bad_point_init(&bp, 10, 20);
    printf("    BadPoint allows direct access: bp.x = %d\n", bp.x);
    bp.x = 999; // Direct modification - breaks encapsulation
    printf("    Can be modified directly: bp.x = %d (BAD!)\n", bp.x);
    printf("\n");

    printf("  GOOD Example:\n");
    GoodPoint *gp = good_point_create(10, 20);
    printf("    GoodPoint uses accessors: x = %d\n", good_point_get_x(gp));
    good_point_set_x(gp, 999);
    printf("    Modified via setter: x = %d\n", good_point_get_x(gp));
    printf("    ✓ Implementation can change without affecting users\n");
    good_point_destroy(gp);
    printf("\n");

    printf("Principle 3: Module Cohesion\n");
    printf("  High Cohesion (GOOD):\n");
    printf("    - Module has single, well-defined purpose\n");
    printf("    - Functions are related and work together\n");
    printf("    - Example: queue.c - all functions manage queue\n");
    printf("  Low Cohesion (BAD):\n");
    printf("    - Module does many unrelated things\n");
    printf("    - Functions don't belong together\n");
    printf("    - Example: utils.c with math, string, and I/O functions\n");
    printf("  ✓ Aim for high cohesion\n\n");

    printf("Principle 4: Module Coupling\n");
    printf("  Loose Coupling (GOOD):\n");
    printf("    - Modules have minimal dependencies\n");
    printf("    - Changes in one module rarely affect others\n");
    printf("    - Well-defined interfaces between modules\n");
    printf("  Tight Coupling (BAD):\n");
    printf("    - Modules depend on each other's internals\n");
    printf("    - Changes ripple across modules\n");
    printf("    - Hard to modify or test independently\n");
    printf("  ✓ Aim for loose coupling\n\n");

    printf("Principle 5: API Design\n");
    printf("  Guidelines:\n");
    printf("    1. Keep API minimal - expose only what's needed\n");
    printf("    2. Use consistent naming conventions\n");
    printf("    3. Make common operations easy\n");
    printf("    4. Validate input parameters\n");
    printf("    5. Return meaningful error codes\n");
    printf("    6. Document behavior clearly\n");
    printf("    7. Consider future extensibility\n");
    printf("  Example naming pattern:\n");
    printf("    module_type_action() → queue_item_enqueue()\n");
    printf("  ✓ Good APIs are intuitive and hard to misuse\n\n");

    printf("Principle 6: Header File Organization\n");
    printf("  Recommended structure:\n");
    printf("    1. Header guard (or #pragma once)\n");
    printf("    2. Documentation comment\n");
    printf("    3. System includes\n");
    printf("    4. Local includes\n");
    printf("    5. Macro definitions\n");
    printf("    6. Type definitions\n");
    printf("    7. Function declarations\n");
    printf("    8. Inline functions (if any)\n");
    printf("    9. Closing guard comment\n\n");

    printf("Principle 7: Implementation File Organization\n");
    printf("  Recommended structure:\n");
    printf("    1. Documentation comment\n");
    printf("    2. Include own header first\n");
    printf("    3. System includes\n");
    printf("    4. Local includes\n");
    printf("    5. Private macros and constants\n");
    printf("    6. Private type definitions\n");
    printf("    7. Static (private) function declarations\n");
    printf("    8. Public function implementations\n");
    printf("    9. Static function implementations\n\n");

    printf("=== Component Design Checklist ===\n");
    printf("✓ Does module have single responsibility?\n");
    printf("✓ Is implementation hidden from users?\n");
    printf("✓ Are dependencies minimal?\n");
    printf("✓ Is API intuitive and consistent?\n");
    printf("✓ Are error conditions handled?\n");
    printf("✓ Is memory ownership clear?\n");
    printf("✓ Are resources properly cleaned up?\n");
    printf("✓ Is module testable in isolation?\n");
    printf("✓ Is code well-documented?\n");
    printf("✓ Can implementation change without breaking users?\n\n");

    printf("=== Common Anti-Patterns ===\n");
    printf("❌ God Objects - modules that do everything\n");
    printf("❌ Exposed Internals - public struct fields\n");
    printf("❌ Circular Dependencies - A needs B, B needs A\n");
    printf("❌ Global State - shared mutable globals\n");
    printf("❌ Inconsistent Naming - different patterns per module\n");
    printf("❌ Leaky Abstractions - implementation details leak out\n");
    printf("❌ Fragile Dependencies - changes break other modules\n\n");

    printf("=== Benefits of Good Componentization ===\n");
    printf("1. Maintainability - easier to understand and modify\n");
    printf("2. Reusability - components work in different contexts\n");
    printf("3. Testability - test components independently\n");
    printf("4. Scalability - add features without breaking existing code\n");
    printf("5. Team Development - different people work on different modules\n");
    printf("6. Version Control - cleaner merge conflicts\n");
    printf("7. Documentation - interface documents itself\n");

    return EXIT_SUCCESS;
}

/*
 * NOTES:
 *
 * 1. Opaque Types (Information Hiding):
 *    Header file:
 *      typedef struct point Point;  // Forward declaration
 *      Point *point_create(int x, int y);
 *
 *    Implementation file:
 *      struct point {  // Full definition
 *          int x, y;
 *      };
 *
 *    Benefits:
 *    - Users can't access fields directly
 *    - Implementation can change freely
 *    - Binary compatibility maintained
 *
 * 2. Module Cohesion Levels:
 *    - Functional: All parts work toward single purpose (BEST)
 *    - Sequential: Output of one is input to next
 *    - Communicational: Work on same data
 *    - Procedural: Follow specific sequence
 *    - Temporal: Executed at same time
 *    - Logical: Similar but unrelated operations
 *    - Coincidental: No meaningful relationship (WORST)
 *
 * 3. Module Coupling Types:
 *    - Data: Share simple data (BEST)
 *    - Stamp: Share composite data
 *    - Control: One controls flow of another
 *    - External: Share global data
 *    - Common: Access common data area
 *    - Content: One modifies another's data (WORST)
 *
 * 4. API Design Principles:
 *    - Consistency: Similar operations have similar names
 *    - Orthogonality: Operations are independent
 *    - Symmetry: Related operations are paired (create/destroy)
 *    - Simplicity: Make simple things simple
 *    - Completeness: Provide all necessary operations
 *    - Safety: Hard to use incorrectly
 *
 * 5. Naming Conventions:
 *    Functions: module_action() or module_type_action()
 *    Types: ModuleType or module_type_t
 *    Constants: MODULE_CONSTANT
 *    Macros: MODULE_MACRO
 *
 * 6. Memory Ownership:
 *    Be explicit about who owns memory:
 *    - Create functions allocate, destroy functions free
 *    - Document if user must free returned pointers
 *    - Use const for borrowed references
 *    - Consider reference counting for shared objects
 *
 * 7. Error Handling:
 *    Strategies:
 *    - Return bool (success/failure)
 *    - Return pointer (NULL on error)
 *    - Return int (0 success, negative error code)
 *    - Out parameter for result, return error code
 *    - Set errno (POSIX convention)
 *
 * 8. Real-World Example Structure:
 *
 *    // vector.h
 *    #ifndef VECTOR_H
 *    #define VECTOR_H
 *
 *    typedef struct vector Vector;
 *
 *    Vector *vector_create(void);
 *    void vector_destroy(Vector *v);
 *    bool vector_push(Vector *v, int value);
 *    bool vector_pop(Vector *v, int *value);
 *    size_t vector_size(const Vector *v);
 *
 *    #endif
 *
 *    // vector.c
 *    #include "vector.h"
 *    #include <stdlib.h>
 *
 *    struct vector {
 *        int *data;
 *        size_t size;
 *        size_t capacity;
 *    };
 *
 *    // ... implementations ...
 */
