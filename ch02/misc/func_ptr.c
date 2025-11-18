#include <stdio.h>

// Define the typedefs from your example
typedef unsigned int uint_type;
typedef signed char schar_type, *schar_p, (*fp)(void);

// 1. Create a function that matches the 'fp' signature:
//    - Takes (void)
//    - Returns signed char
signed char get_a_value(void) {
    printf("Inside get_a_value()\n");
    return -5;
}

signed char get_another_value(void) {
    printf("Inside get_another_value()\n");
    return 120;
}

int main() {
    // 2. Declare a variable of type 'fp'
    //    'my_func_ptr' is a pointer to a function.
    fp my_func_ptr;

    // 3. Assign a function to the pointer
    my_func_ptr = &get_a_value; // or just my_func_ptr = get_a_value;

    // 4. Call the function using the pointer
    schar_type result = my_func_ptr(); // or (*my_func_ptr)();
    
    printf("Result: %d\n\n", result); // Prints: -5

    // You can re-assign it to another matching function
    my_func_ptr = &get_another_value;
    result = my_func_ptr();
    printf("Result: %d\n", result); // Prints: 120

    return 0;
}