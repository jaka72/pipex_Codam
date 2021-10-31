/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:50:41 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 19:49:27 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int		status;
	int		childs;
	int		here_doc;
	pid_t	*pids;

	if (argc < 5)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
		ft_putstr_fd("Same as: < infile \"cmd1\" | \"cmd2\" > outfile\n", 2);
		return (EXIT_FAILURE);
	}
	here_doc = !strncmp(argv[1], "here_doc", 9);
	if (here_doc && argc < 6)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Usage: ./pipex here_doc limiter cmd1 cmd2 outfile\n", 2);
		ft_putstr_fd("Same as: cmd1 << limiter | cmd2 >> outfile\n", 2);
		return (EXIT_FAILURE);
	}
	childs = argc - 3;
	pids = pipex_create_child(childs, argv, here_doc);
	status = pipex_child_wait_for_all(pids, childs);
	free(pids);
	exit(status);
}
