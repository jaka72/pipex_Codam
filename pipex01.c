#include "pipex.h"

/*
QUESTIONS
This ignores content of infile, just prints the dir content
	./pipex infile ``ls -l'' ``wc -l'' outfile


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

	while (envp[i] != NULL)
	{	
		printf("%s\n", envp[i]);	
		i++;
	}


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
		fd1 = open("file1.txt", O_RDONLY);

		dup2(fd1, 0);	    // content of the file fd1 goes to stdinput of cat 
		dup2(mypipe[1], 1);	// output of cat becomes 
		//						 write_to_pipe, GOES to PARENT
		close(fd1);
//		write(mypipe[1], , 10);
//		write(fd, buffer, bytesread);


//		char *args[] = {"/bin/grep", "one", "file1.txt", NULL}; // NOT WORKING ????
//		char *args[] = {"/bin/cat", "file1.txt", NULL};   //     WORKING
		char *args[] = {"/bin/cat", NULL};   //     WORKING
//		char *envps[] = {NULL};

//		HERE COMES AS 2nd ARGUMENT THE ARRAY FROM ft_split
//		execve(path_cmd1, cmd1, NULL);
		close(mypipe[1]);
		execve(args[0], args, NULL);

//		die("execve");  // not permitted???
//		printf("a)\n");
		
	} else
	{
		// parent

//		printf("b)\n");
		fd2 = open("file3.txt", O_WRONLY);
		close(mypipe[1]);
		dup2(mypipe[0], 0);
		dup2(fd2, 1);
		close(fd2);
//		dup2(1, mypipe[0]);
//		dup2(fd2, 0);
//		bytesread = read(mypipe[0], buffer, sizeof(buffer));
//		char *ff = ft_split("wc -l", ' ');
		// char *args2[] = {"cat", "-n", NULL};
		char *args2[] = {"wc", "-l", NULL};
		execve("/usr/bin/wc", args2, NULL);
//		printf("d)\n");
		
//		write(fd2, buffer, bytesread);
//		write(1, buffer, bytesread);

//		close(mypipe[0]);
//		close(fd);
//		printf("\nFrom parent:\n\n");
//		buffer[bytesread] = '\0';
//		printf("br: %d\n buffer: \n[%s]\n", bytesread, buffer);
//		wait(NULL);
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