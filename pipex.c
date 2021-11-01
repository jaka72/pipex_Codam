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
	d->infile = argv[1];
	// printf("infile: %s\n", d->infile);
	d->outfile = argv[4];
	d->path_cmd1 = NULL;
	d->path_cmd2 = NULL;
	d->bin_all_paths_cmd1 = NULL;
	d->bin_all_paths_cmd2 = NULL;
	d->cmd1 = get_command(argv[2]);
	d->cmd2 = get_command(argv[3]);
	// SAVE CMD INTO SEPARATE STRING, TO CHECK LATER IF COMMAND EXISTS
	d->command1 = d->cmd1[0];
	d->command2 = d->cmd2[0];
	printf(" Command 1: [%s], Command 2: [%s]\n\n", d->command1, d->command2);
	// 	APPEND '/' AFTER EACH COMMAND
	d->cmd1[0] = ft_strjoin("/", d->cmd1[0]);
	d->cmd2[0] = ft_strjoin("/", d->cmd2[0]);
	return (0);
}


int	free_all()
{
//	free(d->cmd1);
//	free(d->cmd2);
	// int	i;

	// i = 0;
	// while (d->cmd1[i] != NULL)
	// {
	// 	free(d->cmd1[i]);
	// 	i++;
	// }
	// free(d->cmd1);
	
	// i = 0;
	// while (d->cmd2[i] != NULL)
	// {
	// 	free(d->cmd2[i]);
	// 	i++;
	// }
	// free(d->cmd2);


//	free(d->bin_all_paths_cmd1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
//	atexit(check); // ask dvan-kir
//	int	i;
	t_data	d;

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

	if (pipe(d.pipe_end) == -1)
			return (-1);

	d.pid1 = fork();
	printf("fork1 pid1: %d\n", d.pid1);

	if (d.pid1 == 0)
	{
		d.pid2 = fork();
		if (d.pid2 == 0)
		{		// child
			printf("   fork2 child pid2: %d\n", d.pid2);
			close(d.pipe_end[0]);	// read_from_pipe not needed
			d.fd1 = open(d.infile, O_RDONLY);
			if (d.fd1 < 0)
			{
				perror("pipex: Infile cannot be opened; bash");
				printf("...infile: %s\n", d.infile); // THIS IS PRINTED ONLY AT END
//				printf("%s", d.infile);
				free_all();
				system("leaks pipex");
				exit(0);
//				return (-1);
			}
			dup2(d.fd1, 0);
			dup2(d.pipe_end[1], 1);
			close(d.fd1);
			close(d.pipe_end[1]);
			execve(d.path_cmd1, d.cmd1, NULL);
		} 
		else
		{		// parent
			printf("   fork2 parrent, pid2: %d\n", d.pid2);
			close(d.pipe_end[1]);			// why is this TRUNC ????
			d.fd2 = open(d.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (d.fd2 < 0)
			{
				perror("pipex: Outfile cannot be opened; bash");
//				free_all(&d);
//				printf("%s", d.outfile);
				return (-1);
			}
			dup2(d.pipe_end[0], 0); // read from pipe becomes stdin
			dup2(d.fd2, 1);		//  file becomes destination (output)
			close(d.fd2);
			close(d.pipe_end[0]);
//			wait(NULL); 		// THIS WAIT PREVENTS TO CONTINUT, NOTHING COMES TO OUTFILE
			execve(d.path_cmd2, d.cmd2, NULL);
		}
		printf("Before wait() - this is not printed\n ...");
		wait(NULL); // This is in the parent, waiting for the child to finish
		printf("After second fork\n ...");
	}
//	else
//	{
//		wait(NULL);
//	}



///// FREE ALL /////////////////////////////////////////

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

