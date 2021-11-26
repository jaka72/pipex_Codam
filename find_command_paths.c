/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_command_paths.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 15:22:23 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/24 14:57:17 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_n_free(char *s1, char const *s2)
{
	char	*newstr;

	newstr = ft_strjoin(s1, s2);
	if (newstr == NULL)
		return (NULL);
	free(s1);
	return (newstr);
}

// APPEND CMD_1 TO END OF EACH PATH
int	append_cmd1_to_all_paths(t_data *d)
{
	int	i;

	i = 0;
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		d->bin_all_paths_cmd1[i] = ft_strjoin_n_free(d->bin_all_paths_cmd1[i],
				"/");
		d->bin_all_paths_cmd1[i] = ft_strjoin_n_free(d->bin_all_paths_cmd1[i],
				d->cmd1[0]);
		if (d->bin_all_paths_cmd1[i] == NULL)
			free_all(d, 0);
		i++;
	}
	return (0);
}

// APPEND CMD_2 TO END OF EACH PATH
int	append_cmd2_to_all_paths(t_data *d)
{
	int	i;

	i = 0;
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
		d->bin_all_paths_cmd2[i] = ft_strjoin_n_free(d->bin_all_paths_cmd2[i],
				"/");
		d->bin_all_paths_cmd2[i] = ft_strjoin_n_free(d->bin_all_paths_cmd2[i],
				d->cmd2[0]);
		if (d->bin_all_paths_cmd2[i] == NULL)
		{
			free_all(d, 0);
		}
		i++;
	}
	return (0);
}

// IF access() RETURNS ERROR, IT DOES NOT MATTER, BECAUSE LATER
// THE execve() WILL RETURN ERROR, IF THE PATH IS NOT CORRECT
int	find_correct_path_of_cmd(t_data *d)
{
	int	i;

	i = 0;
	while (d->bin_all_paths_cmd1[i] != NULL)
	{
		if (access(d->bin_all_paths_cmd1[i], X_OK) == 0)
			d->path_cmd1 = d->bin_all_paths_cmd1[i];
		i++;
	}
	i = 0;
	while (d->bin_all_paths_cmd2[i] != NULL)
	{
		if (access(d->bin_all_paths_cmd2[i], X_OK) == 0)
			d->path_cmd2 = d->bin_all_paths_cmd2[i];
		i++;
	}
	return (0);
}

// FIND THE PATH IN ENVP[], AND SPLIT IT INTO SEPARATE PATHS
int	find_paths(char *envp[], t_data *d)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{	
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			d->envp_path = envp[i];
			d->bin_all_paths_cmd1 = ft_split(d->envp_path, ':');
			d->bin_all_paths_cmd2 = ft_split(d->envp_path, ':');
		}
		i++;
	}
	return (0);
}
