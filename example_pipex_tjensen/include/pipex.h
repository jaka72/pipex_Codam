/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:15:26 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 19:32:42 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

# include "libft.h"

// PIPEX CHILD
pid_t	*pipex_create_child(int childs, char *argv[], bool heredoc);
void	pipex_child(int childs, int child_n, int **pipes, char **argv);
int		pipex_child_execute(int pipe_r, int pipe_w, char *cmd_str);
int		pipex_pipes_close(int **pipes, int childs, int child_n);

// PIPEX CMD
char	**pipex_cmd_get(char const *cmd_str, int *status);
int		pipex_cmd_set_path(char **cmd);

// PIPEX PIPES
int		**pipex_pipes_array_get(int n);
void	pipex_pipes_array_destroy(int **array, int rows);

// PIPEX UTILS
int		pipex_open(char *file, int options, int rights);
int		pipex_child_wait_for_all(pid_t *pid, int n);
int		pipex_print_error(char *before, char *message, char *after);

#endif
