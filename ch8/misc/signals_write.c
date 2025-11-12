#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sigrecord
{
    int signum;
    char signame[10];
    char sigdesc[100];
} sigrecord;

int main(void)
{
    int status = EXIT_SUCCESS;
    FILE *fp;
    sigrecord sigrec;

    if ((fp = fopen("ch8/misc/signals.dat", "wb")) == NULL)
    {
        fputs("Cannot open signals.dat file\n", stderr);
        return EXIT_FAILURE;
    }

    sigrecord sigrec30 = {30, "USR1", "user-defined signal 1"};
    sigrecord sigrec31 = {
        .signum = 31, .signame = "USR2", .sigdesc = "user-defined signal 2"};

    size_t size = sizeof(sigrecord);

    if (fwrite(&sigrec30, size, 1, fp) != 1)
    {
        fputs("Cannot write sigrec30 to signals.dat file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    if (fwrite(&sigrec31, size, 1, fp) != 1)
    {
        fputs("Cannot write sigrec31 to signals.dat file\n", stderr);
        status = EXIT_FAILURE;
    }

close_files:
    if (fclose(fp) == EOF)
    {
        fputs("Failed to close file\n", stderr);
        status = EXIT_FAILURE;
    }

    return status;
}
