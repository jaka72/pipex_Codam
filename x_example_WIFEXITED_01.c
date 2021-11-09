// C code to find the exit status of child process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 

/*
	IF execve IS EXECUTED, IT RETURNS 0 OR ANOTHER NUMBER, IF THERE WAS AN MERROR
	BUT S PROBLEM IS, IF THE PATH WAS NOT FOUND, THEN execve DOES NOT EXECUTE, BUT status WILL BE 0,
	JUST AS IF IT EXECUTED SUCCESFULY
*/

int main(void)
{
	pid_t pid = fork();
	int err;
	int status;
	char *cmd1[] = {"catxxx", "infile", NULL};

	 
	if ( pid == 0 )
	{
		// COMMAND sh
	   /* The pathname of the file passed to execl() is not defined   */
		//err = execl("/bin/sh", "bin/sh", "-c", "./nopath", "NULL");             // exit status 127
		//err = execl("/bin/shxxx", "bin/shxxx", "-c", "./nopath", "NULL");     		// exit status 0
		//execl("/bin/sh", "bin/sh", "-c", "/bin/sh", "NULL");              // exit status 0

		// COMMAND ping
		//err = execlp("pingxxxx", "pingxxxx", "-c", "1", "googlexxxx.com", NULL);         // exit status 68
		err = execlp("ping", "ping", "-c", "1", "googlexxxx.com", NULL);            // exit status 0
		//err = execlp("xxping", "xxxping", "-c", "1", "google.com", NULL); // exit status 0

		// COMMAND cat
		//err = execve("/bin/catxxx", cmd1, NULL);                                   // exit status 0
		//err = execve("/bin/xcat", cmd1, NULL);                                    // exit status 0  ?? HOW CAN THIS BE SUCCESS exitcode 0?
		if (err < 0)
			printf("Error > 0:  %d\n", err);
	}
 
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if ( WIFEXITED(status) )
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status == 0)
				printf("Success cmd: code %d\n", exit_status);
			else
				printf("   Exit status of the child was %d\n", exit_status);
		}
	}
	return 0;
}