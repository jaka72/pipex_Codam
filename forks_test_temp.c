#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h>

# define BLKB "\e[40m"
# define HYEL "\e[0;93m"
# define HGRN "\e[0;92m"
# define HWHT "\e[0;97m"
# define YEL   "\e[0;33m"
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RES   "\x1B[0m"

// WORKING, WITHOUT BIG PIPE AND LOOP, I FORGOT TO EXECUTE FUNCTION pipe();
// int main(void)
// {
// 	int i;
// 	int fork_0, fork_1;  // pid_t
// 	int fd1, fd2, fd3, fd4;
// 	char *arr1[] = {"cat", NULL};
// 	char *arr2[] = {"wc", NULL};
// 	int nr_commands;
// 	int small_pipe[2];

// 	printf("\nA) Main, before loop(), pid%d\n\n", getpid());
//     i = 0;
//     nr_commands = 1;

// 	if (pipe(small_pipe) == -1)
// 			return (-1);

// 		fork_0 = fork();

// 		if (fork_0 == 0)
// 		{
// 			printf("   Aa Child 1), Before Second fork, i:%d\n", i);
// 			fork_1 = fork();
// 			printf(MAG"     B) Inside Second fork\n"RES);
// 			if (fork_1 == 0)
// 			{
// 				// child
// 				printf(CYN"         Bchild, Begin i:%d, Do command 1\n"RES, i);
// 				close(small_pipe[0]);
// 				fd1 = open("infile", O_RDONLY);
// 				dup2(fd1, 0);
// 				dup2(small_pipe[1], 1);
// 				close(small_pipe[1]);
// 				close(fd1); // maybe can be immediately after open, after dup2
// 				printf("   end child\n");
// 				execve("/bin/cat", arr1, NULL);
// 			}
// 			else if (fork_1 != 0)
// 			{
// 				// parent
// 				//wait(NULL);
// 				printf(CYN"         Bparent) Begin i:%d, Do command 2\n"RES, i);
// 				close(small_pipe[1]);
// 				fd2 = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 				dup2(fd2, 1);
// 				dup2(small_pipe[0], 0);
// 				close(small_pipe[0]);
// 				close(fd2);
// 				execve("/usr/bin/wc", arr2, NULL);
// 			}
// 	//		i++;
// 			printf("A) After if/else ... \n\n");  // THIS NEVER COMES
// 		}
// 		else if (fork_0 != 0)
// 		{
// 			// PARENT 0 - THIS NEVER COMES
// 			// THIS APPARENTLY IS THE SAME AS OUTSIDE OF if else
// 			//wait(NULL);
// 			printf(GRN"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n", i, getpid());  // this never comes
// 			// i++;
// 		}
// 		//wait(NULL);
// 		printf(YEL"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n\n", i, getpid());  // this never comes
// 			i++;
// //	}
// 	return (0);
// }



/////////////////////////////////////////////////////////////
// SIMILAR TO pipex.c,  BUT IT SAYS BAD FILE DESCRIPTOR
// int main(void)
// {
// 	int i;
// 	int fork_0, fork_1;  // pid_t
// 	int fd1, fd2, fd3, fd4;
// 	char *arr1[] = {"cat", NULL};
// 	char *arr2[] = {"wc", NULL};
// 	int nr_commands;
// 	int small_pipe[2];

// 	printf("\nA) Main, before loop(), pid%d\n\n", getpid());
//     i = 0;
//     nr_commands = 1;

// 		fork_0 = fork();

// 		if (fork_0 == 0)
// 		{
// 			printf("   Aa Child 1), Before Second fork, i:%d\n", i);
// 			fork_1 = fork();
// 			printf(MAG"     B) Inside Second fork\n"RES);
// 			if (fork_1 == 0)
// 			{
// 				// child
// 				printf(CYN"         Bchild, Begin i:%d, Do command 1\n"RES, i);
// 				close(small_pipe[0]);
// 				fd1 = open("infile", O_RDONLY);
// 				dup2(fd1, 0);
// 				dup2(small_pipe[1], 1);
// 				close(small_pipe[1]);
// 				close(fd1); // maybe can be immediately after open, after dup2
// 				printf("   end child\n");
// 				execve("/bin/cat", arr1, NULL);
// 			}
// 			else if (fork_1 != 0)
// 			{
// 				// parent
// 				//wait(NULL);
// 				printf(CYN"         Bparent) Begin i:%d, Do command 2\n"RES, i);
// 				close(small_pipe[1]);
// 				fd2 = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 				dup2(fd2, 1);
// 				dup2(small_pipe[0], 0);
// 				close(small_pipe[0]);
// 				close(fd2);
// 				execve("/usr/bin/wc", arr2, NULL);
// 			}
// 	//		i++;
// 			printf("A) After if/else ... \n\n");  // THIS NEVER COMES
// 		}
// 		else if (fork_0 != 0)
// 		{
// 			// PARENT 0 - THIS NEVER COMES
// 			// THIS APPARENTLY IS THE SAME AS OUTSIDE OF if else
// 			//wait(NULL);
// 			printf(GRN"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n", i, getpid());  // this never comes
// 			// i++;
// 		}
// 		wait(NULL);
// 		printf(YEL"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n\n", i, getpid());  // this never comes
// 			i++;
// //	}
// 	return (0);
// }


/////////////////////////////////////////////////////////////
// NOT WORKING - WITH 2 FORKS, BIG AND SMALL PIPE, AND A LOOP
int main(void)
{
	int i;
	int fork_0, fork_1;  // pid_t
	int fd1, fd2, fd3, fd4;
	char *arr1[] = {"cat", NULL};
	char *arr2[] = {"wc", NULL};
	int nr_commands;
	int small_pipe[2], big_pipe[2];

	printf("\nA) Main, before loop(), pid%d\n\n", getpid());
    i = 0;
    nr_commands = 3;

	pipe(big_pipe);
	// pipe(small_pipe);


	while (i < nr_commands)
	{
		pipe(small_pipe);
		fork_0 = fork();

		printf(YEL"A Loop i:%d, before first if/else\n"RES, i);

		if (fork_0 != 0)
		{
			printf("   A_child 1), Before Second fork, i:%d\n", i);
			fork_1 = fork();
			printf(MAG"     B) Inside Second fork\n"RES);
			if (fork_1 != 0)
			{
				// child
				printf(CYN"         B_child, Begin i:%d, Do command 1\n"RES, i);
				close(small_pipe[0]);
				close(big_pipe[1]);
				if (i == 0)
				{
					printf("             B_child if\n");
					fd1 = open("infile", O_RDONLY);
					dup2(fd1, 0);
				}
				else
				{
					printf("             B_child else\n");
					dup2(big_pipe[0], 0);
				}
				dup2(small_pipe[1], 1);
				close(small_pipe[1]);
				close(fd1); // maybe can be immediately after open, after dup2
				//printf("   end child\n");
				execve("/bin/cat", arr1, NULL);
			}
			else if (fork_1 == 0)
			{
				// parent
				//wait(NULL);
				printf(CYN"         B_parent) Begin i:%d, Do command 2\n"RES, i);
				close(small_pipe[1]);
				close(big_pipe[0]);
				if (i == nr_commands - 1)
//				if (i == 0)
				{
					printf("             B_parent if\n");
					fd2 = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
					dup2(fd2, 1);
				}
				else
				{
					printf("             B_parent else\n");
//					dup2(big_pipe[1], 1);
				}
				dup2(small_pipe[0], 0);
				close(small_pipe[0]);
				close(fd2);
				//wait(NULL);
				execve("/usr/bin/wc", arr2, NULL);
			}
	//		i++;
			printf("A) After if/else ... \n\n");  // THIS NEVER COMES
		}
		else if (fork_0 != 0)
		{
			printf(GRN" A) PARENT 0, i:%d, After it's child finished the 2 commands, pid:%d\n", i, getpid());  // this never comes
			//break ;
			// PARENT 0 - THIS NEVER COMES
			// THIS APPARENTLY IS THE SAME AS OUTSIDE OF if else
			//wait(NULL);
			// i++;
		}
		//system ("lsof -c a.out");
		wait(NULL);
//		close(small_pipe[0]);
//		close(small_pipe[1]);

		printf(GRN"A) PARENT 0, i:%d, After it's child finished the 2 commands, pid:%d\n\n", i, getpid());  // this never comes
		i++;
	}
	printf("A)END \n\n");  // THIS NEVER COMES

	return (0);
}








/////////////////////////////////////////////
// ONLY WITH DOCUMENTS --------------------
// int main(void)
// {
// 	int i;
// 	int fork0, fork1;  // pid_t
// 	int fd1, fd2, fd3, fd4;
// 	char *arr1[] = {"cat", NULL};
// 	char *arr2[] = {"wc", NULL};
// 	int nr_commands;

// 	printf("\nA) Main, before loop(), pid%d\n\n", getpid());
//     i = 0;
//     nr_commands = 5;

// //	fork0 = fork();
// 	while (i < nr_commands)
// 	{
// 		fork0 = fork();	
// 		printf(YEL"A Loop i:%d, before first if/else\n"RES, i);

// 		if (fork0 == 0)
// 		{
// 			printf("   Aa Child 1), Before Second fork, i:%d\n", i);
// 			fork1 = fork();
// 			printf(MAG"     B) Inside Second fork\n"RES);
// 			if (fork1 == 0)
// 			{
// 				// child
// 				printf(CYN"         B child), Begin i:%d, Do command 1\n"RES, i);
// 				fd1 = open("infile", O_RDONLY);
// 				fd2 = open("outfile", O_RDWR | O_TRUNC, 0644);
// 				dup2(fd1, 0);
// 				dup2(fd2, 1);
// 				close(fd1);
// 				close(fd2);
// 				execve("/bin/cat", arr1, NULL);
// 			}
// 			else if (fork1 != 0)
// 			{
// 				// parent
// 				wait(NULL);
// 				printf(CYN"         B parent) Begin i:%d, Do command 2\n"RES, i);
// 				fd3 = open("outfile", O_RDONLY);
// 				fd4 = open("outfile_2", O_RDWR | O_TRUNC, 0644);
// 				dup2(fd3, 0);
// 				dup2(fd4, 1);
// 				close(fd3);
// 				close(fd4);
// 				execve("/usr/bin/wc", arr2, NULL);
// 			}
// 	//		i++;
// 			printf("A) After if/else ... \n\n");  // THIS NEVER COMES
// 		}
// 		else if (fork0 != 0)
// 		{
// 			// PARENT 0 - THIS NEVER COMES
// 			// THIS APPARENTLY IS THE SAME AS OUTSIDE OF if else
// 			//wait(NULL);
// 			printf(GRN"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n\n", i, getpid());  // this never comes
// 			// i++;
// 		}
// 		wait(NULL);
// 		printf(YEL"A) PARENT 0, i:%d, Parent 0, After it's child finished the 2 commands, pid:%d\n\n", i, getpid());  // this never comes
// 			i++;
// 	}
// 	return (0);
// }
