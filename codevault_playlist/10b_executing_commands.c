#include "header.h"
/*
EXECUTING COMMANDS WITH EXECLP(), LIKE ping ...
tHEY NEED TO BE IN CHILD PROCES, BECAUSE THEY TAKE OVER, (REPLACES) THE ENTIRE
PROCESS. NOTHING CAN COME AFTER THE COMMAND, IT WILL NOT WORK
*/

int main(int argc, char *argv)
{
	int pid = fork();
	if (pid == -1) return -1;

	if (pid == 0)
	{
		// child process
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
			//		could be also other things, like FIFO
			//		  execlp("mkfifo", "mkfifo", "sum", nULL);;
		printf("After execlp! Cannot happen.\n"); // this does not happen
	} else {
		// parent process
		wait(NULL);
		printf("In parent, after child is finished!\n");
	}
	printf("END;  execlp() finished, then no more fork, continued in the parent.\n");

	
	return (0);
}