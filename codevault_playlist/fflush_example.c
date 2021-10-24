#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) {

   char buff[1024];
   
   memset( buff, '\0', sizeof( buff ));
   
   //setvbuf(stdout, buff, _IOFBF, 1024);


   fprintf(stdout, "Going to set full buffering on\n");
   
   //setvbuf(stdout, buff, _IOFBF, 1024);

   fprintf(stdout, "This is tutorialspoint.com\n");
	setvbuf(stdout, buff, _IOFBF, 1024);
   
   fprintf(stdout, "This output will go into buff\n");
   //fflush( stdout );

   
   fprintf(stdout, "and this will appear when programm\n");
   fprintf(stdout, "will come after sleeping 5 seconds\n");
   
   sleep(2);
     return(0);
}