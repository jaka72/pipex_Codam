/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 14:10:12 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/18 11:20:11 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	check_if_local_commands_OLD(t_data *d)
// {
// 	if (d->command1[0] == '.' && d->command1[1] == '/')
// 	{
// 		d->cmd1_is_local = 1;
// 		d->path_cmd1 = d->command1;
// 	}
// 	if (d->command2[0] == '.' && d->command2[1] == '/')
// 	{
// 		d->cmd2_is_local = 1;
// 		d->path_cmd2 = d->command2;
// 	}
// 	return (0);
// }

// In func check_if_local ...
// Add argv argument to check if local commands
//    In this func add access check for argv [2] and [3]
//    Remove all checking for ./
//		Also, change it in header and in init_data...
// In func init_data ...
//		Remove joining / with command
//	instead, add another join_and_free in 2 functions append...
//		where in loop each path gets appended and / at the end
//		

int	check_if_local_commands(t_data *d, char *argv[])
{
	if (access(argv[2], X_OK) == 0)
		d->path_cmd1 = argv[2];
	if (access(argv[3], X_OK) == 0)
		d->path_cmd2 = argv[3];

	// if (d->command1[0] == '.' && d->command1[1] == '/')
	// {
	// 	d->cmd1_is_local = 1;
	// 	d->path_cmd1 = d->command1;
	// }
	// if (d->command2[0] == '.' && d->command2[1] == '/')
	// {
	// 	d->cmd2_is_local = 1;
	// 	d->path_cmd2 = d->command2;
	// }
	return (0);
}


int	check_args_and_get_data(t_data *d, int argc, char *envp[], char *argv[])
{
	if (argc != 5)
	{
		dup2(2, 1);
		printf("pipex error: $RES_REAL: ambiguous redirect\n");
		exit(1);
	}
	init_data_and_get_commands(argv, d);
	find_paths(envp, d);
	append_cmd1_to_all_paths(d);
	append_cmd2_to_all_paths(d);
	find_correct_path_of_cmd(d);
	return (0);
}

void	execute_command_1(t_data *d)
{
	int	err;

	close(d->pipe_end[0]);
	d->fd1 = open(d->infile, O_RDONLY);
	if (d->fd1 < 0)
	{
		dup2(2, 1);
		printf("pipex error: %s: No such file or directory", d->infile);
		exit(1);
	}
	dup2(d->fd1, STDIN_FILENO);
	dup2(d->pipe_end[1], STDOUT_FILENO);
	close(d->fd1);
	close(d->pipe_end[1]);
	err = execve(d->path_cmd1, d->cmd1, NULL);
	if (err == -1)
	{
		dup2(2, 1);
		printf("2 pipex error: %s: command not found\n", d->command1);
		exit(127);
	}
}

//waitpid(d.pid2, &wstatus, 0);  // IS THIS REALLY NECESSARY NOW?
// IS IT NECESSARY TO CHECK waitpid IN PARENT OF THE INNER CHILD?
void	execute_command_2(t_data *d)
{
	int	err;

	wait(&d->pid2);
	close(d->pipe_end[1]);
	d->fd2 = open(d->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d->fd2 < 0)
	{
		perror("pipex error");
		free_all(d, 1);
	}
	dup2(d->pipe_end[0], STDIN_FILENO);
	dup2(d->fd2, STDOUT_FILENO);
	close(d->fd2);
	close(d->pipe_end[0]);
	err = execve(d->path_cmd2, d->cmd2, NULL);
	if (err == -1)
	{
		dup2(2, 1);
		printf("pipex error: %s: command not found\n", d->command2);
		exit(127);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	d;
	int		wstatus;

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
		if (d.pid2 == 0)
			execute_command_1(&d);
		else if (d.pid2 > 0)
			execute_command_2(&d);
	}
	close(d.pipe_end[0]);
	close(d.pipe_end[1]);
	waitpid(d.pid1, &wstatus, 0);
	if (wstatus != 0)
		free_all(&d, wstatus / 256);
	free_all(&d, 0);
}
