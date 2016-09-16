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
    int fd, ret_val, count, numread, wr, num, num3, num4, val;
    char buf[MAX_BUF_SIZE];
    char buf2[MAX_BUF_SIZE];
    char buf3[MAX_BUF_SIZE];
    char buf4[MAX_BUF_SIZE];

    /* Create the named - pipe */
    ret_val = mkfifo(NP1, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
	exit(1);
    }

//  printf("Is the network busy? 1 for YES. 0 for NO.\n");
//  scanf("%d", &val);
//  if(val == 0){
    /* Open and Read  */
    fd = open(NP1, O_RDONLY);
    numread = read(fd, buf, MAX_BUF_SIZE);
    buf[numread] = '\0';
    printf("1. Base Station 1 Reads: %s \n", buf); // reads initial message
    printf("\n");

    /**/ sleep(3); //pause before sending off, just so we can see path of events

    /* Write to BS2 */
    wr = open(NP2, O_WRONLY);
    write(wr, buf, strlen(buf));


    /* Create the named - pipe */
    ret_val = mkfifo(NP5, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
      }

    /* Open and read from BS 2 */
    fd = open(NP5, O_RDONLY);
    num = read(fd, buf2, MAX_BUF_SIZE);
    buf2[num] = '\0';
    printf("5. Base Station 1 Reads: %s \n", buf2);

  /**/ sleep(3); //pause before sending off, just so we can see path of events

    /* Write to Mobile 1 */
    wr = open(NP6, O_WRONLY);
    write(wr, buf2, strlen(buf2));

/* ----------------- New Stuff ------------------ */
    ret_val = mkfifo(NP7, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
      }

/* Open and Read from mobile 1  */
    fd = open(NP7, O_RDONLY);
    num3 = read(fd, buf3, MAX_BUF_SIZE);
    buf3[num3] = '\0';
    printf("7. Base Station 1 Reads: %s \n", buf3);

  /**/ sleep(3); //pause before sending off, just so we can see path of events

/* Write to Base Station 2 */
    wr = open(NP8, O_WRONLY);
    write(wr, buf3, strlen(buf3));

    ret_val = mkfifo(NP11, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
      }

/* Open and Read from Base 2  */
    fd = open(NP11, O_RDONLY);
    num4 = read(fd, buf4, MAX_BUF_SIZE);
    buf4[num4] = '\0';
    printf("11. Base Station 1 Reads: %s \n", buf4);

  /**/ sleep(3); //pause before sending off, just so we can see path of events

/* Write to Mobile 1 */
    wr = open(NP12, O_WRONLY);
    write(wr, buf4, strlen(buf4));// change variables
//    } // End master 'If'
//else{
  //call busy
//  printf("ERROR.\n");
  /* Open and Read  */
//  fd = open(NP1, O_RDONLY);
//  numread = read(fd, buf, MAX_BUF_SIZE);
//  buf[numread] = '\0';
//}


}
