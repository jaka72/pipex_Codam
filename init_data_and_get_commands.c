/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data_and_get_commands.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:08:44 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/25 16:50:59 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_code(t_data *d)
{
	if (d->exit_code == 126)
		exit(126);
	exit(127);
}

//	perror("pipex perror: ambiguous redirect");
int	check_args_and_get_data(t_data *d, int argc, char *envp[], char *argv[])
{
	if (argc != 5)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("  Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	init_data_and_get_commands(argv, d);
	find_paths(envp, d);
	append_cmd1_to_all_paths(d);
	append_cmd2_to_all_paths(d);
	find_correct_path_of_cmd(d);
	return (0);
}

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
	d->cmd1_can_execute = 1;
	d->cmd2_can_execute = 1;
	d->exit_code = 0;
	d->err = 0;
	return (0);
}
