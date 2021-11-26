/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 14:10:12 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/26 11:01:25 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ALSO CHECKING IF LOKAL OR ORIGINAL
int	check_command_1(t_data *d)
{
	if (access(d->path_cmd1, X_OK) == 0 && d->cmd1[0][0] != '/'
		&& d->cmd1[0][0] != '.')
		d->path_cmd1 = d->path_cmd1;
	else if (d->cmd1[0][0] == '/')
	{
		ft_putstr_fd("pipex error: cmd1, No such file or directory\n", 2);
		d->cmd1_can_execute = 0;
	}
	else if (d->cmd1[0][0] != '.' && d->cmd1[0][1] != '/')
		ft_putstr_fd("pipex error: Command not found\n", 2);
	else if (access(d->cmd1[0], X_OK) == 0)
		d->path_cmd1 = d->cmd1[0];
	else
	{
		if (errno == 2)
		{
			d->cmd1_can_execute = 0;
			ft_putstr_fd("pipex error: cmd1, No such file or directory\n", 2);
		}
		else
			perror("\npipex error, cmd1");
	}
	return (0);
}

// ALSO CHECKING IF LOKAL OR ORIGINAL
int	check_command_2(t_data *d)
{
	if (access(d->path_cmd2, X_OK) == 0 && d->cmd2[0][0] != '/'
		&& d->cmd2[0][0] != '.')
		d->path_cmd2 = d->path_cmd2;
	else if (access(d->path_cmd2, X_OK) == 0 && (d->cmd2[0][0] == '/'
		|| d->cmd2[0][0] == '.'))
		d->cmd2_can_execute = 0;
	else if (d->cmd2[0][0] == '/')
	{
		ft_putstr_fd("pipex error: cdm2, No such file or directory\n", 2);
		free_all(d, 127);
	}
	else if (d->cmd2[0][0] != '.' && d->cmd2[0][1] != '/')
		ft_putstr_fd("pipex error: Command not found\n", 2);
	else if (access(d->cmd2[0], X_OK) == 0)
		d->path_cmd2 = d->cmd2[0];
	else
	{
		perror("pipex error, cmd1");
		if (errno == 13)
			d->exit_code = 126;
	}
	return (0);
}

void	execute_command_1(t_data *d)
{
	close(d->pipe_end[0]);
	d->fd1 = open(d->infile, O_RDONLY);
	if (d->fd1 < 0)
	{
		perror("pipex error");
		exit(1);
	}
	dup2(d->fd1, STDIN_FILENO);
	dup2(d->pipe_end[1], STDOUT_FILENO);
	close(d->fd1);
	close(d->pipe_end[1]);
	check_command_1(d);
	if (d->cmd1_can_execute == 1)
		d->err = execve(d->path_cmd1, d->cmd1, NULL);
	if (d->err == -1)
		exit(127);
}

void	execute_command_2(t_data *d)
{
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
	check_command_2(d);
	if (d->cmd2_can_execute == 1)
		d->err = execve(d->path_cmd2, d->cmd2, NULL);
	else
	{
		ft_putstr_fd("pipex error: cdm2, No such file or directory\n", 2);
		free_all(d, 127);
	}
	if (d->err == -1)
		exit_with_code(d);
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
