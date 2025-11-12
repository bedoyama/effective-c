#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("fred.txt", "w+");
    if (fp == NULL)
    {
        fputs("Cannot open fred.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    // Write some data to the file
    if (fputs("First line\nSecond line\nThird line\n", fp) == EOF)
    {
        fputs("Cannot write to fred.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    // Current position is at end of file
    long int pos_before = ftell(fp);
    printf("Position before rewind: %ld\n", pos_before);

    // rewind() moves position back to beginning and clears error indicators
    rewind(fp);

    // Verify we're back at the beginning
    long int pos_after = ftell(fp);
    printf("Position after rewind: %ld\n", pos_after);

    // Read the first line to demonstrate we're at the beginning
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("Read after rewind: %s", buffer);
    }

    if (fclose(fp) == EOF)
    {
        fputs("Failed to close file\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
