#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Escape sequences demonstration
    printf("Newline:\nNext line\n\n");
    printf("Tab:\tTabbed text\n");
    printf("Backslash: \\\n");
    printf("Double quote: \"\n");
    printf("Single quote: '\n");
    printf("Backspace: ABC\b\bX\n");
    printf("Carriage return: Hello\rWorld\n");
    printf("Alert (beep): \a\n");

    return EXIT_SUCCESS;
}
