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
    size_t size = sizeof(sigrecord);

    if ((fp = fopen("ch08/misc/signals.dat", "rb")) == NULL)
    {
        fputs("Cannot open signals.dat file\n", stderr);
        return EXIT_FAILURE;
    }

    // read the second signal
    if (fseek(fp, size, SEEK_SET) != 0)
    {
        fputs("fseek in signals.dat file failed\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    if (fread(&sigrec, size, 1, fp) != 1)
    {
        fputs("Cannot read from signals.dat file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    printf(
        "Signal\n  number = %d\n  name = %s\n  description = %s\n\n",
        sigrec.signum, sigrec.signame, sigrec.sigdesc);

close_files:
    fclose(fp);
    return status;
}
