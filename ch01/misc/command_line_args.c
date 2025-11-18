#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc);

    if (argc > 1)
    {
        printf("\nArguments:\n");
        for (int i = 1; i < argc; i++)
        {
            printf("  argv[%d]: %s\n", i, argv[i]);
        }
    }
    else
    {
        printf("\nNo command-line arguments provided.\n");
        printf("Try running: %s arg1 arg2 arg3\n", argv[0]);
    }

    return EXIT_SUCCESS;
}
