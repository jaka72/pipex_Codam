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
	printf("Before 1st fork()\n");
	printf("A) getpid: %d (parent)\n\n", getpid());

	int id = fork();

//	printf("   After 1st fork()\n");
//	printf("   AA) id: %8d (child),  getpid: %d (parent)\n\n", id, getpid());

	int n;
	if (id == 0)
	{
		// child
//		printf("   Before 2nd fork\n");
//		printf("   B) id: %8d (child),  getpid: %d (parent)\n\n", id, getpid());

//		int id2 = fork();

//		printf("      After 2nd fork\n");
//		printf("      BB) id: %8d (child),  getpid: %d (parent)\n\n", id2, getpid());

		n = 1;
	}
	else
	{
		// parent
		n = 10;
		wait(NULL);
	}

	int i = n;
	while (i < n + 5)
	{
		printf(" %2d ", i);
		fflush(stdout);  // to print immediately to terminal, not accumulate in buffer
		i++;
	}
	if (id != 0)
		printf("\n");

	//int pid = fork();

	//if (pid == 0)
	//{
		// child process 
		//int err = execlp("cat", "cat", "file01.txt", NULL);
	//}

	return 0;
}