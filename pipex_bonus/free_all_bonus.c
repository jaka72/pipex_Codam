/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 15:50:01 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/24 13:29:07 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_for_children(t_data *d, int *wstatus)
{
	while (wait(wstatus) != -1)
	{
		if (*wstatus / 256 != 0)
			d->exit_code = *wstatus / 256;
	}
}

void	free_cmd_arr(t_data *d, int i)
{
	i = 0;
	while (d->command_arr[i] != NULL)
	{
		if (d->command_arr[i] != NULL)
			free(d->command_arr[i]);
		d->command_arr[i] = NULL;
		i++;
	}
	free(d->command_arr);
}

void	free_all_paths_cmd(t_data *d, int i)
{
	i = 0;
	while (d->all_paths_arr[i] != NULL)
	{
		free(d->all_paths_arr[i]);
		d->all_paths_arr[i] = NULL;
		i++;
	}
	free(d->all_paths_arr);
}

//	system("leaks pipex");
int	free_all(t_data *d, int exit_code)
{
	int	i;

	i = 0;
	if (d->command_arr != NULL)
		free_cmd_arr(d, i);
	free_all_paths_cmd(d, i);
	if (d->outfile_opened)
		close(d->fd_outfile);
	if (d->err == -1)
		exit_code = 127;
	exit(exit_code);
}
