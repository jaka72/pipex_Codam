/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 14:10:12 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/11 14:14:00 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	reset_data_and_get_commands(char *argv[], t_data *d)
{
	d->infile = argv[1];
	d->outfile = argv[4];
	d->path_cmd1 = NULL;
	d->path_cmd2 = NULL;
	d->bin_all_paths_cmd1 = NULL;
	d->bin_all_paths_cmd2 = NULL;
	d->cmd1 = NULL;
	d->cmd2 = NULL;
	d->cmd1 = ft_split(argv[2], ' ');
	d->cmd2 = ft_split(argv[3], ' ');
	if (d->cmd1 == NULL || d->cmd2 == NULL)
		free_all(d, 0);
	d->command1 = d->cmd1[0];
	d->command2 = d->cmd2[0];
	d->cmd1[0] = ft_strjoin("/", d->cmd1[0]);
	d->cmd2[0] = ft_strjoin("/", d->cmd2[0]);
	if (d->cmd1[0] == NULL || d->cmd2[0] == NULL) // PROBABLY NECESSARY, BECAUSE NEEDS TO FREE 
		free_all(d, 0);
	return (0);
}

// IS IT NECESSARY TO CHECK waitpid IN PARENT OF THE INNER CHILD?
int	check_args_and_get_data(t_data *d, int argc, char *envp[], char *argv[])
{
	if (argc != 5)
	{
		perror("pipex error: There should be 4 arguments, bash");
		exit(1);
	}
	reset_data_and_get_commands(argv, d);
	find_paths(envp, d);
	append_cmd1_to_all_paths(d);
	append_cmd2_to_all_paths(d);
	find_correct_path_of_cmd(d);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	d;
	int	err;
	int wstatus;

	check_args_and_get_data(&d, argc, envp, argv);
	if (pipe(d.pipe_end) == -1)
			return (-1);

	d.pid1 = fork();
	if (d.pid1 == -1)
		free_all(&d, 1);
	
	if (d.pid1 == 0)
	{
		d.pid2 = fork();
		if (d.pid2 == -1)
			free_all(&d, 1);
		if (d.pid2 == 0)			// child
		{
			close(d.pipe_end[0]);
			d.fd1 = open(d.infile, O_RDONLY);
			if (d.fd1 < 0)
			{
				perror("pipex_error: fd1 == -1; zsh");
				exit(1);
			}
			dup2(d.fd1, STDIN_FILENO);
			dup2(d.pipe_end[1], STDOUT_FILENO);
			close(d.fd1);
			close(d.pipe_end[1]);
			printf("path cmd1: [%s]\n", d.path_cmd1);
			err = execve(d.path_cmd1, d.cmd1, NULL);
			if (err == -1)
			{
				perror("pipex error: command 1 not found; zsh");
				exit(127);
			}
		}
		else if (d.pid2 > 0)			// parent
		{
			//waitpid(d.pid2, &wstatus, 0);  // IS THIS REALLY NECESSARY NOW?
			close(d.pipe_end[1]);
			d.fd2 = open(d.outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (d.fd2 < 0)
			{
				perror("pipex error: fd2 == -1; zsh");
				free_all(&d, 1);
			}
			dup2(d.pipe_end[0], STDIN_FILENO);
			dup2(d.fd2, STDOUT_FILENO);
			close(d.fd2);
			close(d.pipe_end[0]);
			err = execve(d.path_cmd2, d.cmd2, NULL);
			if (err == -1)
			{
				perror("pipex error: command 2 not found; zsh");
				exit(127);
			}
		}
	}
	close(d.pipe_end[0]);
	close(d.pipe_end[1]);
	waitpid(d.pid1, &wstatus, 0);
	if (wstatus != 0)
		free_all(&d, wstatus / 256);
	free_all(&d, 0);
}
