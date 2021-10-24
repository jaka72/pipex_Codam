#include "header.h"


int main(void)
{
	int fd[2];
	pipe(fd);

	int id = fork();
	if (id == 0) {
		close(fd[0]);
		int x;
		printf("This is in child process.\nInput number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	} else {
		close(fd[1]);
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("\nNow this is in parent process.\n");
		printf("Read from the pipe: %d\n", y);
		printf("This %d was scanned in child process and then written into the pipe, inside child process.\n", y);
	}


	return 0;
}