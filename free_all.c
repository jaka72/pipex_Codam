/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 15:50:01 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/11 18:10:54 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd1_arr(t_data *d, int i)
{
	i = 0;
	while (d->cmd1[i] != NULL)
	{
		if (d->cmd1[i] != NULL)
			free(d->cmd1[i]);
		d->cmd1[i] = NULL;
		i++;
	}
	free(d->cmd1);
}

void	free_cmd2_arr(t_data *d, int i)
{
	i = 0;
	while (d->cmd2[i] != NULL)
	{
		free(d->cmd2[i]);
		i++;
	}
	free(d->cmd2);
}

void	free_all_paths_cmd1(t_data *d, int i)
{
	i = 0;
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		free(d->bin_all_paths_cmd1[i]);
		d->bin_all_paths_cmd1[i] = NULL;
		i++;
	}
	free(d->bin_all_paths_cmd1);
}

void	free_all_paths_cmd2(t_data *d, int i)
{
	i = 0;
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
		free(d->bin_all_paths_cmd2[i]);
		d->bin_all_paths_cmd2[i] = NULL;
		i++;
	}
	free(d->bin_all_paths_cmd2);
}

//	system("leaks pipex");
int	free_all(t_data *d, int exit_code)
{
	int	i;

	i = 0;
	free_cmd1_arr(d, i);
	free_cmd2_arr(d, i);
	free_all_paths_cmd1(d, i);
	free_all_paths_cmd2(d, i);
	exit(exit_code);
}
