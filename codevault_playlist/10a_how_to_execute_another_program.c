#include "header.h"


/*
_exec functions overwrites the main process, and execution order, so nothing else can happen after it. 

_execl()	needs the whole path to the program
_execlp()	path not needed, l = list
_execvp()	path not needed, v = vector
*/

int main(int argc, char *argv, char *envp[])
{	
//	windows	 /////////////////////																	// last must be null pointer
//	_execl("C:\\Windows\\System32\\ping.exe", ":C:\\Windows\\System32\\ping.exe", "google.com", NULL);

//	LINUX //////////////////////////
//	EXECL()
//	execl("/bin/ping", "/bin/ping", "-c", "1", "google.com", NULL);

//	EXECLP
//	execlp("ping", "ping", "google.com", NULL);


//	EXECVP()    // takes an array of arguments
	char *arr[] = {"ping", "-c", "1", "yahoo.com", NULL};
	execvp("ping2", arr);
	
//	EXECLPE() ????  not working
	char *env[] = {"TEST=environment variable", NULL};
//	execlpe("ping", "ping", "google.com", env);

	int err = errno;

	printf("Ping finished executing\n");

	// int pid = fork();
	// if (pid == -1) return -1;

	// if (pid == 0) // child process
	// {

	// } else {
		
	
	return (0);
}