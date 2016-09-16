#include <stdlib.h> //
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h" /* For name of the named-pipe */

int main(){
    int fd, ret_val, count, numread, wr, num, num3, num4;
    char buf[MAX_BUF_SIZE];
    char buf2[MAX_BUF_SIZE];
    char buf3[MAX_BUF_SIZE];
    char buf4[MAX_BUF_SIZE];

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
    printf("2. Base Station 2 Reads : %s \n", buf);
    printf("\n");

    sleep(3); //pause before sending off, just so we can see path of events

    /* Write to MS2 */
    wr = open(NP3, O_WRONLY);
    write(wr, buf, strlen(buf));

    /* Create the named - pipe */
    ret_val = mkfifo(NP4, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
          perror("Error creating the named pipe");
          exit(1);
        }

    /* Open and read from Mobile 2 */
    fd = open(NP4, O_RDONLY);
    num = read(fd, buf2, MAX_BUF_SIZE);
    buf2[num] = '\0';
    printf("4. Base Station 2 Reads : %s \n", buf2);

    sleep(3); //pause before sending off, just so we can see path of events

    /* Write to BS1 */
    wr = open(NP5, O_WRONLY);
    write(wr, buf2, strlen(buf2));

    /* ----------------- New Stuff ------------------ */
    /* Create the named - pipe */
    ret_val = mkfifo(NP8, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
          perror("Error creating the named pipe");
          exit(1);
        }

    /* Open and read from Base Station 1 */
    fd = open(NP8, O_RDONLY);
    num3 = read(fd, buf3, MAX_BUF_SIZE);
    buf3[num3] = '\0';
    printf("8. Base Station 2 Reads : %s \n", buf3);

    sleep(3); //pause before sending off, just so we can see path of events

    /* Write to Mobile 2 */
    wr = open(NP9, O_WRONLY);
    write(wr, buf3, strlen(buf3));

    /* Create the named - pipe */
    ret_val = mkfifo(NP10, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
          perror("Error creating the named pipe");
          exit(1);
        }

    /* Open and read from Mobile 2 */
    fd = open(NP10, O_RDONLY);
    num4 = read(fd, buf4, MAX_BUF_SIZE);
    buf4[num4] = '\0';
    printf("10. Base Station 2 Reads : %s \n", buf4);

    sleep(3); //pause before sending off, just so we can see path of events

    /* Write to Base 1 */
    wr = open(NP11, O_WRONLY);
    write(wr, buf4, strlen(buf4));

  }
