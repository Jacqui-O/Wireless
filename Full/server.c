/* Server = Base Station 1 or Base Station 2 */
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h" /* For name of the named-pipe */

int main(int argc, char *argv[])
{
    int rdfd, wrfd, ret_val, count, numread;
    char buf[MAX_BUF_SIZE];

    /* Create the first named - pipe */
    ret_val = mkfifo(NP1, 0666);

    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
    }

    ret_val = mkfifo(NP2, 0666);

    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
    }

    /* Open the first named pipe for reading from mobile 1 */
    rdfd = open(NP1, O_RDONLY);

    /* Open the second named pipe for writing to Base Station 2 */
    wrfd = open(NP2, O_WRONLY);

    /* Read from the first pipe; read from mobile 1 */
    numread = read(rdfd, buf, MAX_BUF_SIZE); // contains Hello message

    buf[numread] = '\0';

    printf("Full Duplex Server : Read From the pipe : %s\n", buf);

    /* Convert to the string to upper case */
    count = 0;
    while (count < numread) {
        buf[count] = toupper(buf[count]);
        count++;
    }

    /*
     * Write the converted string back to the second
     * pipe
     */
    write(wrfd, buf, strlen(buf));
}

