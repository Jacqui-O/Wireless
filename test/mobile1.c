// Mobile 1
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h"

// To run this as Mobile 1, type ./mobile1 "Call Setup"

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

      /*-------------- More new stuff -----------------*/
    //  if()
        // mobile 1 tries to send a message to bs1.  if the bs1 is off, there is no response
            // if not a success message, try again 3 times

      /* Open and read from Base Station 1 */
      fd = open(NP6, O_RDONLY);
      numread = read(fd, buf, MAX_BUF_SIZE);
      buf[numread] = '\0';
      printf("Read From the pipe : %s ", buf); //success message

  /**/ sleep(3); 

      /* Write to base 1 */
      printf("Mobile 1 wants to end the call.");
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
// run this program first, then bs2, server, then mobile2
   else{
     /* Create the named pipe */
     ret_val = mkfifo(NP3, 0666);
     if ((ret_val == -1) && (errno != EEXIST)) {
         perror("Error creating the named pipe");
     exit(1);
     }

     /* Open and read from BS2 */
     fd = open(NP3, O_RDONLY);
     numread = read(fd, buf, MAX_BUF_SIZE); //changed from numread
     buf[numread] = '\0';

  /**/ sleep(3); //pause before sending off, just so we can see path of events
     // go through checks
     printf("Choose an option. Enter a number 1-4:\n(Must enter the number twice.)\n");
     printf("1. MS busy\n2. MS unavailable\n3. Network Busy\n4. Call Forward\n5. MS turned off\n6. Line Available\nEnter: ");
     scanf("%d", &input); //remove \n. Only request a scan once.  With it, expects a scan twice

     if(input ==1){
         printf("This MS is busy.\n");
         char str[] = {"Busy Tone."};
         wr = open(NP4, O_WRONLY);
         write(wr, str, strlen(str));
     }
     else if(input ==2){
         printf("The MS is unavailable\n");
         char str[] = {"Call Dropped."};
         wr = open(NP4, O_WRONLY);
         write(wr, str, strlen(str));
         }
     else if(input ==3){
       //  i=0;
           while(i<4){
             printf("Attempt %d\n", i);
             printf("Is the network still busy: 1 for YES. 0 for NO.\n");
             scanf("%d", &busy);
             printf("Wait 3 seconds...\n");
               if(busy == 1){
                 i++;
                 sleep(3); // time to wait before retry
               }
               else if(busy ==0){
                 printf("Network now available. Message '%s' received.\n", buf);
                 char str[] = {"Connected.\n"};
                 wr = open(NP4, O_WRONLY);
                 write(wr, str, strlen(str));
                 //exit(1);
               }
               else {
                 printf("You didn't enter the correct numbers. Default to busy.\n");
                 i=4; //break out of loop.
             }
         } // End while
         printf("Network still busy.\n");
         char str[] = {"Disconnect.\n"};
         wr = open(NP4, O_WRONLY);
         write(wr, str, strlen(str));
     }
     else if (input == 4){
       printf("Call Forwared. Message '%s' received.\n", buf);
       char str[] = {"Success.\n"};
       wr = open(NP4, O_WRONLY);
       write(wr, str, strlen(str));

     }
     else if(input == 5){
       printf("MS is turned off.\n");
       char str[] = {"Voicemail.\n"};
       wr = open(NP4, O_WRONLY);
       write(wr, str, strlen(str));
     }
     else{
       printf("Line Available. Message %s received.\n", buf);
       char str[] = {"Success.\n"};
       wr = open(NP4, O_WRONLY);
       write(wr, str, strlen(str));
     }
   }// end master 'Else'

// Add 3 more pipes for hang up prodedure.  Or 6?

}
