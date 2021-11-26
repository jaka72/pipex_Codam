/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 14:10:12 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/25 16:20:06 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_args_and_init_data(t_data *d, int argc, char *envp[], char *argv[])
{
	if (argc < 5)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("  Usage: ./pipex infile cmd1 cmd2 cmd3 ... outfile\n", 2);
		exit(1);
	}
	init_data(argv, argc, d);
	find_paths(envp, d);
	return (0);
}

int	child(char *argv, t_data *d)
{
	close(d->mypipe[0]);
	dup2(d->fd_temp, 0);
	close(d->fd_temp);
	if (d->i < d->nr_commands + 1)
		dup2(d->mypipe[1], 1);
	else if (d->i == d->nr_commands + 1)
		open_outfile(d);
	close(d->mypipe[1]);
	if (d->command_path != NULL)
		free(d->command_path);
	if (d->command_arr != NULL)
		free_cmd_arr(d, 0);
	get_new_command(argv, d);
	d->err = execve(d->command_path, d->command_arr, NULL);
	if (d->err == -1)
	{
		ft_putstr_fd("pipex error: command not found\n", 2);
		free(d->command_path);
		if (d->i == d->nr_commands + 1)
			exit(127);
		exit(0);
	}
	return (0);
}

int	parent(t_data *d)
{
	close(d->mypipe[1]);
	close(d->fd_temp);
	dup2(d->mypipe[0], d->fd_temp);
	close(d->mypipe[0]);
	return (0);
}

void	make_pipe(t_data *d)
{
	if (pipe(d->mypipe) == -1)
	{
		perror("pipex error, pipe");
		free_all(d, 0);
	}
}

// d->i = 2, start counting commands at argv[2]
//system("lsof -c pipex");
//system("leaks pipex");
int	main(int argc, char *argv[], char *envp[])
{
	t_data	d;
	int		wstatus;

	check_args_and_init_data(&d, argc, envp, argv);
	open_infile(&d);
	while (d.i < d.nr_commands + 2)
	{
		make_pipe(&d);
		d.pid1 = fork();
		if (d.pid1 == -1)
		{
			perror("pipex error, fork");
			free_all(&d, 0);
		}
		if (d.pid1 == 0)
			child(argv[d.i], &d);
		else
			parent(&d);
		d.i++;
	}
	wait_for_children(&d, &wstatus);
	close(d.fd_temp);
	free_all(&d, d.exit_code);
}
