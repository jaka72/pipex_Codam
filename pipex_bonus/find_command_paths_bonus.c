/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command_paths_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 15:22:23 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/24 15:00:28 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_n_free(char *s1, char const *s2)
{
	char	*newstr;

	newstr = ft_strjoin(s1, s2);
	if (newstr == NULL)
		return (NULL);
	free(s1);
	return (newstr);
}

int	find_correct_path_of_cmd(t_data *d)
{
	int		i;

	if (d->command_path != NULL)
	{
		free(d->command_path);
		d->command_path = NULL;
	}
	i = 0;
	while (d->all_paths_arr[i] != NULL)
	{
		d->command_path = ft_strjoin(d->all_paths_arr[i], "/");
		d->command_path = ft_strjoin_n_free(d->command_path, d->command_arr[0]);
		if (access(d->command_path, X_OK) == 0)
		{
			d->command_path = ft_strjoin_n_free(d->command_path, "");
			return (0);
		}
		if (d->command_path != NULL)
		{
			free(d->command_path);
			d->command_path = NULL;
		}
		i++;
	}
	return (0);
}

int	find_paths(char *envp[], t_data *d)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{	
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			d->all_paths_arr = ft_split(envp[i], ':');
		i++;
	}
	return (0);
}
