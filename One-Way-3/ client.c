#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h" /* For name of the named-pipe */

int main(int argc, char *argv[])
{
    int fd;

    /* Check if an argument was specified. */

    if (argc != 2) {
        printf("Usage : %s <string to be sent to the server>\n", argv[0]);
        exit (1);
    }

    /* Open and write  */
    fd = open(NP1, O_WRONLY);
    write(fd, argv[1], strlen(argv[1]));
    // Create NP6
}