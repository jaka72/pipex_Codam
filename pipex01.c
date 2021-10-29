#include "pipex.h"

/*
QUESTIONS
This ignores content of infile, just prints the dir content
	./pipex infile ``ls -l'' ``wc -l'' outfile
*/



/*
fork into 2 processes
In child process, call exec cm1, with input file1
	child returns some result, gives it into the pipe,
	which goes to parent process

Parent waits for the child to finish
	Takes, reads the result of the child from the pipe
	Performs cmd2
	Prints the result into outfile

	pipe[0]  =>  read_from_pipe
	pipe[1]  =>  write_to_pipe

*/


// Ask dvan-kri
// int check_at_exit()
// {
// 		; 
// }


char **get_arguments(char *argv2)
{
	int		i;
	char	**cmd1;

//	printf("%s\n", argv1);	

	cmd1 = ft_split(argv2, ' ');
	i = 0;
	while (cmd1[i] != NULL)
	{	
		printf("i%d,  %s\n", i, cmd1[i]);	
		i++;
	}	
	return (cmd1);
}


int	main(int argc, char *argv[], char *envp[])
{
//	atexit(check); // ask dvan-kir

// use the function access() !!!!
// 		to check if the program in the path exists and if it is executable

	int		i;
	int		pid;
	int		mypipe[2];
	int		fd2;
	int		fd1;
	int		bytesread;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char 	*path_cmd1;
	char 	*path_cmd2;

	infile = argv[1];
	outfile = argv[4];
//	cmd1 = argv[2];
//	cmd2 = argv[3];
	if (pipe(mypipe) == -1)
		return (-1);

	cmd1 = get_arguments(argv[2]);
	// i = 0;
	// while (envp[i] != NULL)
	// {	
	// 	printf("%s\n", envp[i]);	
	// 	i++;
	// }

	path_cmd1 = ft_strjoin("/bin/", cmd1[0]);
	printf("joined: {%s}\n\n", path_cmd1);

	pid = fork();

	if (pid == 0)
	{
		// child
		close(mypipe[0]);	// read_from_pipe not needed
		fd1 = open(infile, O_RDONLY);
		dup2(fd1, 0);	    // content of the file fd1 goes to stdin of cmd_1
		dup2(mypipe[1], 1);	// output of cmd_1 becomes write_to_pipe, GOES to PARENT
		close(fd1);
		close(mypipe[1]);
		char *args[] = {"/bin/cat", NULL};   //     WORKING
		execve(args[0], args, NULL);
	} else 	{
		// parent
		close(mypipe[1]);
		fd2 = open(outfile, O_WRONLY);
		dup2(mypipe[0], 0); // read from pipe becomes stdin
		dup2(fd2, 1);		//  file becomes destination (output)
		close(fd2);
		close(mypipe[0]);
		char *args2[] = {"wc", NULL};
		execve("/usr/bin/wc", args2, NULL);
	}




///// TO FREE //////////////////////////////////////

	// RETURN STR FROM ft_strjoin, 	DOES IT HAVE TO BE FREED??

	// FREE BOTH **ARRAYS cmd1 AND cmd2
	// i = 0;
	// while (cmd1[i] != NULL)
	// {	
	// 	free(cmd1[i]);	
	// 	i++;
	// }
	// free(cmd1);

	printf("\nEnd of main:\n\n");


	return (0);
}