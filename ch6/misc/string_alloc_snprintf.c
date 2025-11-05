#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Safe standard: Using snprintf for guaranteed null-termination
int main(void)
{
    const char *source = "123456789abcdef"; // 15 chars + \0
    size_t buffer_size = 16;

    char *str = (char *)malloc(buffer_size);
    if (!str)
    {
        return EXIT_FAILURE;
    }

    // Use snprintf to "print" the string into the buffer
    // It will copy at most (buffer_size - 1) chars and add \0
    snprintf(str, buffer_size, "%s", source);

    // str is now guaranteed to be "123456789abcdef" with a \0 at str[15]
    // If buffer_size was 10, str would be "123456789" with a \0 at str[9]

    printf("str = %s.\n", str);
    free(str);
    return EXIT_SUCCESS;
}
