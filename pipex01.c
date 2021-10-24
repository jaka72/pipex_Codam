#include "pipex.h"

char **get_arguments(char *argv2)
{
	int		i;
	char	**cmd1;

//	printf("%s\n", argv1);	

	cmd1 = ft_split(argv2, ' ');
	i = 0;
	while (cmd1[i] != NULL)
	{	
		printf("%s\n", cmd1[i]);	
		i++;
	}	
	return (cmd1);
}


int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		pid;
	int		mypipe[2];
	int		fd;
	int		bytesread;
	char	buffer[4000];
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


//	get_arguments(argv[2], argv[3], cmd1, cmd2);
	cmd1 = get_arguments(argv[2]);
//	printf("cmd1[0]: {%s}\n\n", cmd1[0]);

	i = 0;
	// while (cmd1[i] != NULL)
	// {	
	// 	printf("i)\n");
	// 	printf("%s\n", cmd1[i]);	
	// 	i++;
	// }

	path_cmd1 = ft_strjoin("/bin/", cmd1[0]);
//	ft_strjoin("/bin/", cmd1[0]);
//	printf("cmd1[0]: {%s}\n\n", cmd1[0]);
	printf("joined: {%s}\n\n", path_cmd1);

//	printf("%s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);


/*
fork into 2 processes
In child process, call exec cm1, with input file1
	child returns some result, gives it inot the pipe,
	which goes to parent process

Parent waits for the child to finish
	Takes, reads the result of the child from the pipe
	Performs cmd2
	Prints the result into outfile

	pipe[0]  =>  read_from_pipe
	pipe[1]  =>  write_to_pipe

*/

	
//	execlp("wc", "wc", "-w", "file1.txt", NULL);
	pid = fork();
	if (pid == 0)
	{
		// child
		close(mypipe[0]);	// read_from_pipe not needed
		dup2(mypipe[1], 1);	// stdout goes to write_to_pipe
		char *args[] = {"/bin/ls", "-l", "-a", NULL};
		char *envps[] = {NULL};
//		execve(args[0], args, NULL);
//		HERE COMES AS 2nd ARGUMENT THE ARRAY FROM ft_split
			execve(path_cmd1, cmd1, NULL);

//		die("execve");  // not permitted???
//		printf("a)\n");
		close(mypipe[1]);
	} else
	{
		// parent
//		printf("b)\n");
		fd = open("file2.txt", O_WRONLY);
		close(mypipe[1]);
		bytesread = read(mypipe[0], buffer, sizeof(buffer));
//		not clear	dup2(mypipe[0], 0);  // stuff from pipe goes to stdin, which goes to cmd2
//		char *args2[] = {"/bin/wc", "-w", "file2.txt", NULL};
//			execve("/bin/wc", args2, NULL);
		write(fd, buffer, bytesread);
		close(mypipe[0]);
		close(fd);
		printf("From parent:\n\n");
//		printf("%s\n", buffer);

		wait(NULL);

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


	return (0);
}