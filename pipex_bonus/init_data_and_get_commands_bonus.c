/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_and_get_commands_bonus.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:08:44 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/24 15:03:32 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_outfile(t_data *d)
{
	d->fd_outfile = open(d->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d->fd_outfile == -1)
	{
		perror("pipex error, outfile");
		free_all(d, 0);
	}
	else
		d->outfile_opened = 1;
	dup2(d->fd_outfile, 1);
}

// if no infile, it should still create the outfile
void	open_infile(t_data *d)
{
	d->fd_infile = open(d->infile, O_RDONLY);
	if (d->fd_infile == -1)
	{
		perror("pipex error, infile");
		exit(1);
	}
	d->fd_temp = dup(d->fd_infile);
	close(d->fd_infile);
}

int	check_if_local_command(char *command_path, t_data *d)
{
	if (access(command_path, X_OK) == 0)
		d->is_local = 1;
	return (0);
}

// SPLIT COMMAND AND OPTIONS INTO ARRAY
int	get_new_command(char *argv, t_data *d)
{
	d->command_arr = ft_split(argv, ' ');
	check_if_local_command(d->command_arr[0], d);
	if (d->is_local == 1)
	{	
		if (d->command_path != NULL)
			free(d->command_path);
		d->command_path = d->command_arr[0];
		return (0);
	}
	find_correct_path_of_cmd(d);
	return (0);
}

int	init_data(char *argv[], int argc, t_data *d)
{
	d->nr_commands = argc - 3;
	d->i = 2;
	d->infile = argv[1];
	d->outfile = argv[argc - 1];
	d->outfile_opened = 0;
	d->is_local = 0;
	d->command_path = NULL;
	d->all_paths_arr = NULL;
	d->command_arr = NULL;
	d->err = 0;
	d->exit_code = 0;
	return (0);
}
