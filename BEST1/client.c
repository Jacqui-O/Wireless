#include <stdlib.h> //
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "full_duplex.h" /* For name of the named-pipe */

// To run this as Mobile 1, type ./c "message"

int main(int argc, char *argv[]){
    int fd, num, ret_val, input;
    int wr, i=1, busy;
    char buf[MAX_BUF_SIZE];


// If used as the mobile 1
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

      /* Open and read from Mobile 2 */
      fd = open(NP6, O_RDONLY);
      num = read(fd, buf, MAX_BUF_SIZE);
      buf[num] = '\0';
      printf("Read From the pipe : %s ", buf);
    } // end 'If'
// create specific print statements depending on what was received.
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
     num = read(fd, buf, MAX_BUF_SIZE); //changed from numread
     buf[num] = '\0';

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
                 exit(1);
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
       char str[] = {"Connected.\n"};
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
       char str[] = {"Connected.\n"};
       wr = open(NP4, O_WRONLY);
       write(wr, str, strlen(str));
     }
   }// end master 'Else'

// Add 3 more pipes for hang up prodedure.  Or 6?

}
