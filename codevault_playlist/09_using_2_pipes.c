#include "header.h"
/*
USING TWO PIPES
 p[0] => read from pipe, pipe outputs
 p[1] => write to pipe, pipe receives 
*/

int main(int argc, char *argv)
{
	int pipe1[2];
	int pipe2[2];
	if (pipe(pipe1) == -1) {return 1;}
	if (pipe(pipe2) == -1) {return 1;}
	int pid = fork();
	if (pid == -1) {return 2;}

	if (pid == 0) {
		close(pipe1[0]);
		close(pipe2[1]); 
		int x;
		if (read(pipe2[0], &x, sizeof(int)) == -1)
			return 3;
		printf("received: %d\n", x);
		x = x * 4;
		if (write(pipe1[1], &x, sizeof(int)) == -1)
			return 4;
		close(pipe1[1]);
		close(pipe2[0]);
	} 
	else {
		close(pipe1[1]);
		close(pipe2[0]);
		int y = 3;
		write(pipe2[1], &y, sizeof(int));
		int result;
		read(pipe1[0], &y, sizeof(int));
		close(pipe1[0]); 
		close(pipe2[1]);
		printf("result: %d\n", y);
		wait(NULL);
	}

	return (0);
}