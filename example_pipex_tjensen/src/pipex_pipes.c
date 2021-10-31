/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:34:56 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 19:32:01 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	**pipex_pipes_array_mem(int n);

int	**pipex_pipes_array_get(int n)
{
	int	i;
	int	**pipes;

	pipes = pipex_pipes_array_mem(n);
	if (pipes == NULL)
		exit(ENOMEM);
	i = 0;
	while (i < n)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror(NULL);
			pipex_pipes_array_destroy(pipes, n);
			exit(errno);
		}
		i++;
	}
	return (pipes);
}

void	pipex_pipes_array_destroy(int **array, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

static int	**pipex_pipes_array_mem(int n)
{
	int	i;
	int	**pipes;

	pipes = malloc(n * sizeof(int *));
	if (pipes == NULL)
		exit(ENOMEM);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
			exit(ENOMEM);
		i++;
	}
	return (pipes);
}
