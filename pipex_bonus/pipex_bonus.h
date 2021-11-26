/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaka <jaka@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 10:28:50 by jaka          #+#    #+#                 */
/*   Updated: 2021/11/24 13:29:46 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <stdio.h> 
# include <errno.h> 
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct data
{
	int			i;
	int			err;
	int			exit_code;
	int			nr_commands;
	pid_t		pid1;
	int			mypipe[2];
	int			fd2;
	int			fd1;
	int			fd_temp;
	int			fd_infile;
	int			fd_outfile;
	int			outfile_opened;
	char		*infile;
	char		*outfile;
	char		**command_arr;
	char		*command_path;
	int			is_local;
	char		**all_paths_arr;
}	t_data;

int		init_data(char *argv[], int argc, t_data *d);
int		find_paths(char *envp[], t_data *d);
int		check_if_local_command(char *command, t_data *d);
int		get_new_command(char *argv, t_data *d);
int		find_correct_path_of_cmd(t_data *d);
void	free_cmd_arr(t_data *d, int i);
int		free_all(t_data *d, int exit_code);
void	open_infile(t_data *d);
void	open_outfile(t_data *d);
void	wait_for_children(t_data *d, int *wstatus);

#endif
