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

int	reset_data_and_get_commands(char *argv[], t_data *d)
{
	// printf("infile: %s\n", d->infile);
	d->infile = argv[1];
	d->outfile = argv[4];
	d->path_cmd1 = NULL;
	d->path_cmd2 = NULL;
	d->bin_all_paths_cmd1 = NULL;
	d->bin_all_paths_cmd2 = NULL;

	d->cmd1 = NULL;
	d->cmd2 = NULL;
	d->cmd1 = get_command(argv[2]);
	d->cmd2 = get_command(argv[3]);
	if (d->cmd1 == NULL || d->cmd2 == NULL)	// ?????? IS THIS NECESSARY ??? 
		free_all(d, 0);						// HOW CAN I FREE HERE OTHER THINGS THAT
											//HAVE NOT BEEN MALLOCED YET ???

	// SAVE CMD INTO SEPARATE STRING, TO CHECK LATER IF COMMAND EXISTS
	d->command1 = d->cmd1[0];
	d->command2 = d->cmd2[0];
	
	// 	APPEND '/' AFTER EACH COMMAND
	d->cmd1[0] = ft_strjoin("/", d->cmd1[0]);
	d->cmd2[0] = ft_strjoin("/", d->cmd2[0]);
	if (d->cmd1[0] == NULL || d->cmd2[0] == NULL) // ??? IS THIS NECESSARY
		free_all(d, 0);
	return (0);
}


void	print_array(t_data *d)
{
	int	i;
	i = 0;
	printf("\n\nARRAY bin_all_paths_cmd1\n");
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		printf("--- %s\n", d->bin_all_paths_cmd1[i]);
		i++;
	}
}



/*
	Testing with Pipexaminator
	Apaprently exit() only exits out of the child process into parent proces. 
	Parent can get the exit code via waitpid, but it is strange: if exit(1), then wstatus is 256.
	I divide it with 256 to get the correct code ???

*/





int	main(int argc, char *argv[], char *envp[])
{
//	atexit(check); // ask dvan-kir
//	int	i;
	t_data	d;
	int	err;
	int wstatus;
//	int statuscode;

//	char *cmd1[] = {"/bin/catx", "-ex", NULL};
//	char *cmd1[] = {"/bin/cat", "-e", NULL};

	if (argc != 5)
	{
		perror("pipex error, There should be 4 arguments, bash");
//		perror("");
		return (0);
	}
	reset_data_and_get_commands(argv, &d);
	find_paths(envp, &d);
	append_cmd1_to_all_paths(&d);
	append_cmd2_to_all_paths(&d);
	find_correct_path_of_cmd(&d);

//	print_array(&d);
//	printf(" ..... path: [%s]\n", d.path_cmd1); fflush(stdout);


	if (pipe(d.pipe_end) == -1)
			return (-1);

	d.pid1 = fork();
//	printf("fork1 pid1: %d\n", d.pid1);
	
	if (d.pid1 == 0)
	{
//		printf("First fork Child\n ");
		d.pid2 = fork();
		if (d.pid2 == 0)
		{		// child
//			printf("   Second fork CHILD   pid2: %d\n", d.pid2);
			close(d.pipe_end[0]);	// read_from_pipe not needed
			d.fd1 = open(d.infile, O_RDONLY);
			if (d.fd1 < 0)
			{
//				perror("pipex: Infile cannot be opened; bash");
//				printf("pipex error: "); fflush(stdout);
				perror("pipex_error");
//				printf("...infile: %s\n", d.infile); // THIS IS PRINTED ONLY AT END
//				free_all(&d, 1);
//				system("leaks pipex");
//				printf("infile: [%s]\n", d.infile);
				exit(1);  // IS THIS EXIT ALLOWED ???
//				printf("after exit .....\n");

//				return (-1);
			}
//			printf(" ..... path: [%s]\n", d.path_cmd1);
			dup2(d.fd1, 0);
			dup2(d.pipe_end[1], 1);
			close(d.fd1);
			close(d.pipe_end[1]);
			printf("path cmd1: [%s]\n", d.path_cmd1);
			err = execve(d.path_cmd1, d.cmd1, NULL);
//			err = execve("/bin/cat",   cmd1, NULL);
			if (err == -1)
			{
				printf("xecve cmd1, err %d, errno %d\n", err, errno);
				perror("  pipex error: From execve cmd1, Bad address. Bash"); // THIS DOES NOT APPEAR AFTER EXEC
				return (0);
			}
		}
		else if (d.pid2 > 0)
		{		// parent
			// IF cmd1 EXECUTED BUT RETURNED ERROR AND EXITED, HOW CAN I DETECT THAT???
			// IT AUTOMATICALY PRINTS ITS OWN ERROR MESSAGE.
			//wait(&wstatus);
			waitpid(d.pid2, &wstatus, 0);
			printf("wstatus: %d\n", wstatus/256);
			if (wstatus != 0)
				exit(wstatus / 256);

			close(d.pipe_end[1]);			// why is this TRUNC ????
			d.fd2 = open(d.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (d.fd2 < 0)
			{
				perror("pipex: Outfile cannot be opened; bash");
				free_all(&d, 1);
//				printf("%s", d.outfile);
				exit(0);
//				return (-1);
			}
			dup2(d.pipe_end[0], 0); // read from pipe becomes stdin
			dup2(d.fd2, 1);		//  file becomes destination (output)
			close(d.fd2);
			close(d.pipe_end[0]);
//			wait(NULL); 		// THIS WAIT PREVENTS TO CONTINUE, NOTHING COMES TO OUTFILE
			err = execve(d.path_cmd2, d.cmd2, NULL);
			if (err == -1)
			{
				printf("Could not find command 2 to execute!\n");
				return (0);
			}
//			free_all(&d);
		}
//
//		free_all(&d);
	}
	else
	{
//		free_all(&d);
		close(d.pipe_end[0]);
		close(d.pipe_end[1]);
	}
	waitpid(d.pid1, &wstatus, 0);
	if (wstatus != 0)
		free_all(&d, wstatus / 256);
	free_all(&d, 0);
	system("leaks pipex");
	printf("\nEnd of main.\n\n");
	exit(0);
//	return (0);
}

