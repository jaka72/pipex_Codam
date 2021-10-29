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


char **get_command(char *argv2)
{
	int		i;
	char	**cmd1;

//	printf("%s\n", argv1);	
	cmd1 = ft_split(argv2, ' ');
	i = 0;
	while (cmd1[i] != NULL)
	{	
//		printf("i%d,  %s\n", i, cmd1[i]);	
		i++;
	}	
	return (cmd1);
}






int	main(int argc, char *argv[], char *envp[])
{
//	atexit(check); // ask dvan-kir

// use the function access() !!!!
// 		to check if the program in the path exists and if it is executable

//	int		i;
	int		pid1;
	int		pid2;
	int		mypipe[2];
	int		fd2;
	int		fd1;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char	*envp_path;
	char	*path_cmd1;
	char	*path_cmd2;
	char	**bin_paths_cmd1;
	char	**bin_paths_cmd2;
//	char 	*path_cmd1;
//	char 	*path_cmd2;

	if (argc < 1)
		return (0);

	infile = argv[1];
	outfile = argv[4];
//	cmd1 = argv[2];
//	cmd2 = argv[3];
	if (pipe(mypipe) == -1)
		return (-1);

	cmd1 = get_command(argv[2]);
	cmd2 = get_command(argv[3]);


// FIND PATHS IN ENVP[]
	int i = 0;
	while (envp[i] != NULL)
	{	
//		printf("%s\n", envp[i]);
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
//			printf("FOUND: %s\n", envp[i]);
			envp_path = envp[i];
//			printf("cmd_path: %s\n", envp_path);
			bin_paths_cmd1 = ft_split(envp_path, ':');
			bin_paths_cmd2 = ft_split(envp_path, ':');
		}
		i++;
	}

	cmd1[0] = ft_strjoin("/", cmd1[0]);
	cmd2[0] = ft_strjoin("/", cmd2[0]);

// APPEND CMD_1 TO END OF PATH
	i = 0;
	while (bin_paths_cmd1[i] != NULL)
	{
		bin_paths_cmd1[i] = ft_strjoin(bin_paths_cmd1[i], cmd1[0]);
		printf("   cmd 1 path: %s\n", bin_paths_cmd1[i]);
		i++;
	}

// APPEND CMD_2 TO END OF PATH
	i = 0;
	while (bin_paths_cmd2[i] != NULL)
	{
		bin_paths_cmd2[i] = ft_strjoin(bin_paths_cmd2[i], cmd2[0]);
		printf("   cmd 2 path: %s\n", bin_paths_cmd2[i]);
		i++;
	}

//	FIND CORRECT PATH OF CMD_1
	i = 0;
	while (bin_paths_cmd1[i] != NULL)
	{
		if (access(bin_paths_cmd1[i], X_OK) == 0)
		{
			printf("\nCorrect path CMD 1: %s\n", bin_paths_cmd1[i]);
			path_cmd1 = bin_paths_cmd1[i];
		}
		i++;	
	}

//	FIND CORRECT PATH OF CMD_2
	i = 0;
	while (bin_paths_cmd2[i] != NULL)
	{
		if (access(bin_paths_cmd2[i], X_OK) == 0)
		{
			printf("\nCorrect path CMD 2: %s\n", bin_paths_cmd2[i]);
			path_cmd2 = bin_paths_cmd2[i];
		}
		i++;	
	}


// CHOOSE CORRECT BIN (COMPARE THE PATH WITH EACH BIN)
//     What is there are programs with same name in different bins ???



//	path_cmd1 = ft_strjoin("/bin/", cmd1[0]);
//	printf("joined: {%s}\n\n", path_cmd1);

	pid1 = fork();

	if (pid1 == 0)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			// child
			close(mypipe[0]);	// read_from_pipe not needed
			fd1 = open(infile, O_RDONLY);
			dup2(fd1, 0);	    // content of the file fd1 goes to stdin, which 
								// will be read by cmd_1
			dup2(mypipe[1], 1);	// output of cmd_1 becomes write_to_pipe, GOES to PARENT
								// without this dup2, nothing writes into pipe
			close(fd1);
			close(mypipe[1]);
//			char *args1[] = {"/bin/cat", NULL};   //     WORKING
			execve(path_cmd1, cmd1, NULL);
		} 
		else
		{
			// parent
			close(mypipe[1]);
			fd2 = open(outfile, O_WRONLY);
			dup2(mypipe[0], 0); // read from pipe becomes stdin
			dup2(fd2, 1);		//  file becomes destination (output)
			close(fd2);
			close(mypipe[0]);
	//		char *args2[] = {"/usr/bin/wc", "-c", NULL};
//			char *args2[] = {"/usr/bin/wc", NULL};
			execve(path_cmd2, cmd2, NULL);
		}
		printf("Before wait() - this is not printed\n ...");
//		wait(NULL);
		printf("After second fork\n ...");
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

