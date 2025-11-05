#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Faster: BSD's strlcpy recommendation
// Note: This code will NOT compile on a standard Windows machine
// You'd need to provide your own strlcpy implementation.
// On some Linux distros: #include <bsd/string.h>

// Fallback strlcpy implementation for portability
// size_t strlcpy(char *dst, const char *src, size_t size)
// {
//     size_t src_len = strlen(src);
//     if (size == 0)
//     {
//         return src_len;
//     }
//     size_t copy_len = (src_len < size - 1) ? src_len : size - 1;
//     memcpy(dst, src, copy_len);
//     dst[copy_len] = '\0';
//     return src_len;
// }

int main(void)
{
    const char *source = "123456789abcdef";
    size_t buffer_size = 16;

    char *str = (char *)malloc(buffer_size);
    if (!str)
    {
        return EXIT_FAILURE;
    }

    // strlcpy is a "safe strcpy"
    strlcpy(str, source, buffer_size);

    // str is now "123456789abcdef" and null-terminated.
    printf("str = %s.\n", str);
    free(str);
    return EXIT_SUCCESS;
}
