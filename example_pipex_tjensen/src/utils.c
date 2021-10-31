/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:38:28 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 19:52:37 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_pipes_close(int **pipes, int childs, int child_i)
{
	int	i;
	int	status;

	status = EXIT_SUCCESS;
	i = 0;
	while (i < (childs - 1))
	{
		if (i != child_i)
		{
			status = close(pipes[i][1]);
			pipes[i][1] = 0;
		}
		if (i != child_i - 1)
		{
			status = close(pipes[i][0]);
			pipes[i][0] = 0;
		}
		i++;
	}
	return (status);
}

int	pipex_child_wait_for_all(pid_t *pid, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	status = status >> 8;
	status = status & 0x000000ff;
	return (status);
}

int	pipex_open(char *file, int options, int rights)
{
	int	fd;

	if (ft_strncmp(file, "here_doc", 8) == 0)
		return (STDIN_FILENO);
	fd = open(file, options, rights);
	if (fd < 0)
		pipex_print_error("pipex", strerror(errno), file);
	return (fd);
}

int	pipex_print_error(char *before, char *message, char *after)
{
	if (before)
		ft_putstr_fd(before, 2);
	if (message)
	{
		if (before)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	if (after)
	{
		if (message)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(after, 2);
	}
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}
