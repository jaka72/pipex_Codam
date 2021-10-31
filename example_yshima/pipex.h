/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:34:23 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/22 12:59:14 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

char	**ft_split(char const *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_trijoin(char const *s1, char const *s2, char const *s3);
void	ft_putstr_fd(char *s, int fd);
void	cmd_err(char *cmd, char **av);
int		ft_open(char *file, int mode, char **av);
char	*get_path(char *cmd, char **envp);
void	perror_exit(char *s);
char	*ft_strdup(const char *src);

#endif