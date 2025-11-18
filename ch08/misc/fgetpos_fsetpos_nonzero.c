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

    // Write initial data
    if (fputs("XXXXXXXXXX", fp) == EOF)
    {
        fputs("Cannot write to fred.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    // Move to position 5 (middle of the file)
    if (fseek(fp, 5, SEEK_SET) != 0)
    {
        fputs("Seek failed\n", stderr);
        return EXIT_FAILURE;
    }

    // Save position at offset 5
    fpos_t saved_pos;
    if (fgetpos(fp, &saved_pos) != 0)
    {
        perror("get position");
        return EXIT_FAILURE;
    }
    printf("Saved position at offset: %ld\n", ftell(fp));

    // Write more data from current position
    if (fputs("YYYYY", fp) == EOF)
    {
        fputs("Cannot write to fred.txt file\n", stderr);
    }

    // Move to end of file
    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fputs("Seek to end failed\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Current position after writing: %ld\n", ftell(fp));

    // Restore to saved position (offset 5)
    if (fsetpos(fp, &saved_pos) != 0)
    {
        perror("set position");
        return EXIT_FAILURE;
    }
    printf("Restored position to offset: %ld\n", ftell(fp));

    // Overwrite from saved position
    if (fputs("ZZZZZ", fp) == EOF)
    {
        fputs("Cannot write to fred.txt file\n", stderr);
    }

    // Read the final result
    rewind(fp);
    char buffer[50];
    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("Final file content: %s\n", buffer);
    }

    if (fclose(fp) == EOF)
    {
        fputs("Failed to close file\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
