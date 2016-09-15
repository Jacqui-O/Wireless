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
    int fd, ret_val, count, numread, wr;
    char buf[MAX_BUF_SIZE];

    /* Create the named - pipe */
    ret_val = mkfifo(NP2, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
	exit(1);
    }

    /* Open and read from BS1 */
    fd = open(NP2, O_RDONLY);
    numread = read(fd, buf, MAX_BUF_SIZE);
    buf[numread] = '\0';
    printf("Half Duplex Server : Read From the pipe : %s \n", buf);

    /* Write to MS2 */
  //  wr = open(NP3, O_WRONLY);
  //  write(wr, buf, strlen(buf));

//Create NP4
}
