/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:43:06 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/25 15:06:33 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_splitfree(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*ft_trijoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !s2 || !s3)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + ft_strlen(s3)) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	k = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	while (s3[++k])
		str[i + j + k] = s3[k];
	str[i + j + k] = '\0';
	return (str);
}

void	cmd_err(char *cmd, char **av)
{
	ft_putstr_fd(ft_trijoin(av[0], ": ", cmd), STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

int	ft_open(char *file, int mode, char **av)
{
	int	fd;

	if (mode == STDIN_FILENO)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			perror(ft_trijoin(av[0], ": ", file));
		return (fd);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			perror(ft_trijoin(av[0], ": ", file));
		return (fd);
	}
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*ret;
	char	**path_each;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	path_each = ft_split(path, ':');
	i = -1;
	while (path_each[++i])
	{
		ret = ft_strdup(ft_trijoin(path_each[i], "/", cmd));
		if (access(ret, F_OK) == 0)
		{
			ft_splitfree(path_each);
			return (ret);
		}
	}
	ft_splitfree(path_each);
	return (0);
}
