// Mobile 2
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include "full_duplex.h"

// To run this as Mobile 1, type ./mobile2 "Call Setup"
int main(int argc, char *argv[]){
  int fd, numread, ret_val, wr, input, i=1, busy, num;
  char buf[MAX_BUF_SIZE];
  char buf2[MAX_BUF_SIZE];


  /* If run as mobile 1 */
  if (argc == 2) {
      /* Open and write  */
      fd = open(NP1, O_WRONLY);
      write(fd, argv[1], strlen(argv[1]));

    /* Create the named - pipe */
    ret_val = mkfifo(NP6, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit(1);
    }

    /* Open and read from Base Station 1 */
    fd = open(NP6, O_RDONLY);
    numread = read(fd, buf, MAX_BUF_SIZE);
    buf[numread] = '\0';
    printf("Read From the pipe : %s ", buf);

    sleep(3); 

    /* Write to base 1 */
    char str[] = {"Terminate.\n"};
    wr = open(NP7, O_WRONLY);
    write(wr, str, strlen(str));

    /* Create the named pipe */
    ret_val = mkfifo(NP12, 0666);
    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
    exit(1);
    }

    /* Open and read from Base Station 1 */
    fd = open(NP12, O_RDONLY);
    num = read(fd, buf2, MAX_BUF_SIZE);
    buf2[num] = '\0';
    printf("Read From the pipe : %s ", buf2);

  } /* end 'If' */

/* --------------------  If used as mobile 2, do below ------------------ */
else{
  /* Create the named pipe */
  ret_val = mkfifo(NP3, 0666);
  if ((ret_val == -1) && (errno != EEXIST)) {
      perror("Error creating the named pipe");
  exit(1);
  }

  /* Open and read from BS2 */
  fd = open(NP3, O_RDONLY);
  numread = read(fd, buf, MAX_BUF_SIZE);
  buf[numread] = '\0';

  /**/ sleep(3); //pause before sending off, just so we can see path of events
  // go through checks

    printf("3. Line Available. Message '%s' received.\n", buf);
    char str[] = {"Success.\n"};
    wr = open(NP4, O_WRONLY);
    write(wr, str, strlen(str));

  /* ----------------- New Stuff ------------------ */
  /* Create the named pipe */
  ret_val = mkfifo(NP9, 0666);
  if ((ret_val == -1) && (errno != EEXIST)) {
      perror("Error creating the named pipe");
      exit(1);
  }
  /* Open and read from BS2 */
  fd = open(NP9, O_RDONLY);
  num = read(fd, buf2, MAX_BUF_SIZE);
  buf2[num] = '\0';

  printf("Received message '%s'", buf2);
  printf("OK. Terminating call.");

  sleep(3); //pause before sending off, just so we can see path of events
  /* Write to BS2 */
  char str1[] = {"Acknowledged.\n"};
  wr = open(NP10, O_WRONLY);
  write(wr, str1, strlen(str1));
}// End master 'Else'

// Add 3 more pipes for hang up prodedure.  Or 6?
}
