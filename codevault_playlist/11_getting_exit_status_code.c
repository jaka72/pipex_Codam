#include "header.h"
/*

- CHECKING IF execlp SUCCEEDS
- CHECKING FOR wait() STATUS

EXECUTING COMMANDS WITH EXECLP(), LIKE ping ...
tHEY NEED TO BE IN CHILD PROCES, BECAUSE THEY TAKE OVER, (REPLACES) THE ENTIRE
PROCESS. NOTHING CAN COME AFTER THE COMMAND, IT WILL NOT WORK
*/

// TRY CHANGING google.com TO google.xyz

int main(int argc, char *argv)
{
	int pid = fork();
	if (pid == -1) return -1;

	if (pid == 0)
	{
		// child process
		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		if (err == -1)
		{
			printf("Could not find program to execute\n");
			return (0);
		}
		printf("After execlp! Cannot happen.\n"); // this does not happen
	} else {
		// parent process
		int wstatus;
//		wait(NULL);
		wait(&wstatus);			// IF wstatus == 0, IT IS A SUCCESS
		if (WIFEXITED(wstatus)) //     ie: WIFEXITED(0)     SUCCESS
		{
			printf("\n   wstatus %d\n", wstatus);
			int status_code = WEXITSTATUS(wstatus);
			if (status_code == 0)
//			if (wstatus == 0)
				printf("   --- Success, status_code %d!\n", status_code);
			else
				printf("   --- Failure, status_code %d!\n", status_code);
		}
		printf("  \nBack in parent, after child is finished!\n");
	}
	printf("END;  execlp() finished, then no more fork, continued in the parent.\n");

	
	return (0);
}