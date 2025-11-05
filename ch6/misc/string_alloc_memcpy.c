#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manual cowboy: Top performance using memcpy
int main(void)
{
    const char *source = "123456789abcdef";
    size_t buffer_size = 16;

    // We want to copy (buffer_size - 1) chars
    size_t copy_len = buffer_size - 1;

    // Make sure the source is not shorter than that
    size_t source_len = strlen(source);
    if (source_len < copy_len)
    {
        copy_len = source_len;
    }

    char *str = (char *)malloc(buffer_size);
    if (!str)
    {
        return EXIT_FAILURE;
    }

    // 1. Copy the bytes (this is very fast)
    memcpy(str, source, copy_len);

    // 2. Manually add the null terminator
    str[copy_len] = '\0';

    printf("str = %s.\n", str);
    free(str);
    return EXIT_SUCCESS;
}
