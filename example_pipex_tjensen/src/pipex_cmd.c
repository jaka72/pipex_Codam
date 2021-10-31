/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:18:29 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 13:39:43 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**environ_path_get(void);
static void	environ_path_append_slash(char **paths);

char	**pipex_cmd_get(char const *cmd_str, int *status)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	if (cmd_args == NULL)
	{
		*status = ENOMEM;
		return (NULL);
	}
	*status = pipex_cmd_set_path(&cmd_args[0]);
	if (*status != 0)
	{
		pipex_print_error("pipex", "command not found", cmd_args[0]);
		ft_free_split(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}

int	pipex_cmd_set_path(char **cmd)
{
	int		i;
	char	*cmd_tmp;
	char	**paths;

	if (access(*cmd, F_OK) == 0)
		return (0);
	paths = environ_path_get();
	if (paths == NULL)
		return (ENOMEM);
	i = 0;
	while (paths[i])
	{
		cmd_tmp = ft_strjoin(paths[i], *cmd);
		if (access(cmd_tmp, F_OK) == 0)
		{
			free(*cmd);
			*cmd = cmd_tmp;
			ft_free_split(paths);
			return (0);
		}
		free(cmd_tmp);
		i++;
	}
	ft_free_split(paths);
	return (127);
}

static char	**environ_path_get(void)
{
	int			i;
	char		**paths;
	extern char	**environ;

	if (environ == NULL)
		return (NULL);
	paths = NULL;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			paths = ft_split((environ[i] + 5), ':');
			if (paths == NULL)
				return (NULL);
			environ_path_append_slash(paths);
			break ;
		}
		i++;
	}
	return (paths);
}

static void	environ_path_append_slash(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}
