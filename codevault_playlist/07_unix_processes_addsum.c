#include "header.h"


int main(void)
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	int arrsize = sizeof(arr) / sizeof(int);
	int fd[2];
	pipe(fd);
	int id = fork();
	int start, end;
	int sum = 0;
	if (id == 0)
	{
		close(fd[0]);
		start = 0;
		while (start < arrsize / 2)
		{
			sum = sum + arr[start];
			start++;
		}
		write(fd[1], &sum, sizeof(int));
		close(fd[1]);
	} else {
		close(fd[1]);
		start = arrsize / 2;
		while (start < arrsize)
		{
			sum = sum + arr[start];
			start++;
		}
		//wait(NULL);
		int received;
		read(fd[0], &received, sizeof(int));
		close(fd[0]);
		printf("Sum: %d\n", sum);
		printf("Received: %d\n", received);
		printf("Totaal sum: %d\n", sum + received);
		wait(NULL);
	}


	return (0);
}
