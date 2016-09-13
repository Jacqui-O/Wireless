/* Client = Mobile 1 or Mobile 2*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h" /* For name of the named-pipe */

int main(int argc, char *argv[])
{
    int wrfd, rdfd, numread;
    char rdbuf[MAX_BUF_SIZE];

    /* Check if an argument was specified. */

    if (argc != 2) {
        printf("Usage : %s <string to be sent to the server>\n", argv[0]);
        exit (1);
    }

    /* Open the first named pipe for writing */
    wrfd = open(NP1, O_WRONLY);

    /* Open the second named pipe for reading */
    rdfd = open(NP2, O_RDONLY);

    /* Write to the pipe. Send a message. */
    write(wrfd, argv[1], strlen(argv[1]));

    // These are possible messages to be read (numread)  from the BS
    // If it takes longer than 1 minute for the call to be answered, send a disconnect
    // message, or disconnect from the BS
    // Otherwise, if receiving a message of ms unavailable, hang up
    // if ms busy, send busy tone message then hang up after five seconds
    // if network busy, wait five seconds then call again 
    // if ms turned off, send to voice mail
    // if answered, talk until disconnect message is sent
    // if hangup, disconnect
    
    /* Read from the pipe */
    numread = read(rdfd, rdbuf, MAX_BUF_SIZE);

    rdbuf[numread] = '\0';

    printf("Full Duplex Client : Read From the Pipe : %s\n", rdbuf);
}
