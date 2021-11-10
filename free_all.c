/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 15:50:01 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/10 09:43:44 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_all(t_data *d)
{
	int	i;

	i = 0;
	while (d->cmd1[i] != NULL)
	{
		printf("  FREE d->cmd1 [%s]\n", d->cmd1[i]);
		free(d->cmd1[i]);
		i++;
	}
	free(d->cmd1);
	

	
	i = 0;
	while (d->cmd2[i] != NULL)
	{
		printf("  FREE d->cmd2 [%s]\n", d->cmd2[i]);
		free(d->cmd2[i]);
//		printf("  FREE d->cmd2 [%s]\n", d->cmd2[i]);

		i++;
	}
	free(d->cmd2);



	i = 0;
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
//		printf("  FREE cmd1 [%s]\n", d->bin_all_paths_cmd1[i]);
		free(d->bin_all_paths_cmd1[i]);
		d->bin_all_paths_cmd1[i] = NULL;
//		printf("  FREED cmd1 [%s]\n", d->bin_all_paths_cmd1[i]);
		i++;
	}
	free(d->bin_all_paths_cmd1);



	i = 0;
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
//		printf("  FREE cmd2[%s]\n", d->bin_all_paths_cmd2[i]);
		free(d->bin_all_paths_cmd2[i]);
		d->bin_all_paths_cmd2[i] = NULL;
//		printf("  FREED cmd2[%s]\n", d->bin_all_paths_cmd2[i]);
		i++;
	}
	free(d->bin_all_paths_cmd2);

	return (0);
}
