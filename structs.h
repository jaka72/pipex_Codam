/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 14:40:18 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/09 13:25:45 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct data
{
	pid_t		pid1;
	pid_t		pid2;
	int		pipe_end[2];
	int		fd2;
	int		fd1;
	char	*command1;
	char	*command2;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char	*envp_path;
	char	*path_cmd1;
	char	*path_cmd2;
	char	**bin_all_paths_cmd1;
	char	**bin_all_paths_cmd2;
} t_data;


/*
ALL	MALLOCS
	pipex_child.c
		pid
	pipex_pipes.c
		pipes
		pipes[i]
	pipex_utils.c
		str
*/