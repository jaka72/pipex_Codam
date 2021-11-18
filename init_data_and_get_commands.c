/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_and_get_commands.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:08:44 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/18 11:13:29 by jaka          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// APPARENTLY NOT NECESSARY, BECAUSE LATER THE exec() 
//		if (d->cmd1[0] == NULL || d->cmd2[0] == NULL) 
//			free_all(d, 0);
int	init_data_and_get_commands(char *argv[], t_data *d)
{
	d->infile = argv[1];
	d->outfile = argv[4];
	d->cmd1_is_local = 0;
	d->cmd2_is_local = 0;
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
	check_if_local_commands(d, argv);
//	if (d->cmd1_is_local == 0)
//		d->cmd1[0] = ft_strjoin("/", d->cmd1[0]);  // INSTEAD OF THIS, APPEND SLASH TO ALL PATHS 
//	if (d->cmd2_is_local == 0)						// WHEN THEY ARE CREATED FROM THE PATH
//		d->cmd2[0] = ft_strjoin("/", d->cmd2[0]);
	return (0);
}
