#include "header.h"


/*
 fork() creates a paralel process, for every process after fork()
	Every process in linux has a process id
	After fork(), you can check a separate id for each of 2 processes
		parent: some number
		child: always 0
		
*/

int main(int argc, char *argv[])
{
	int id = fork();
	if (id == 0)
	{
		// child
		printf("Hello from child: %d\n", id);
	}
	else
	{
		// parent
		wait(NULL);
		printf("Hello from parent: %d\n", id);
	}
	printf("After: %d\n", id);


	return (0);
}