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
    int fd, ret_val, count, numread, wr, num;
    char buf[MAX_BUF_SIZE];
    char buf2[MAX_BUF_SIZE];

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
    printf("Base Station 2 Reads : %s \n", buf);
    printf("\n");
    
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
    printf("Base Station 2 Reads : %s \n", buf2);

    /* Write to BS1 */
    wr = open(NP5, O_WRONLY);
    write(wr, buf2, strlen(buf2));
  }
