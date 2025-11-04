#include <stdio.h>
#include <limits.h> // For CHAR_BIT

int main() {
    printf("Bits in char:        %zu\n", sizeof(char) * CHAR_BIT);
    printf("Bits in short:       %zu\n", sizeof(short) * CHAR_BIT);
    printf("Bits in int:         %zu\n", sizeof(int) * CHAR_BIT);
    printf("Bits in long:        %zu\n", sizeof(long) * CHAR_BIT);
    printf("Bits in long long:   %zu\n", sizeof(long long) * CHAR_BIT);
    // printf("BITINT_MAXWIDTH: %d\n", BITINT_MAXWIDTH) // C23;
    
    return 0;
}