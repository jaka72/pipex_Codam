/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmurovec <jmurovec@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/01 15:41:13 by jmurovec      #+#    #+#                 */
/*   Updated: 2021/11/09 13:03:45 by jmurovec      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_command(char *argv)
{
//	int		i;
	char	**cmd;

//	printf("%s\n", argv1);	
	cmd = ft_split(argv, ' ');

//	PRINT COMMAND ARRAY, WITH OPTIONS
//	i = 0;
// 	while (cmd[i] != NULL)
// 	{	
// //		printf("i%d,  %s\n", i, cmd[i]);	
// 		i++;
// 	}

	return (cmd);
}
