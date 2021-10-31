/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:34:20 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/25 15:05:27 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char *cmd, char **envp, char **av)
{
	char	**sp_cmd;
	char	*path;

	sp_cmd = ft_split(cmd, ' ');
	if (access(sp_cmd[0], X_OK) == 0)
		path = sp_cmd[0];
	else if (ft_strchr(sp_cmd[0], '/'))
	{
		path = 0;
		free(path);
		perror_exit(ft_trijoin(av[0], ": ", cmd));
	}
	else
		path = get_path(sp_cmd[0], envp);
	execve(path, sp_cmd, envp);
	free(path);
	cmd_err(cmd, av);
}

static void	child_2(int fdout, int *fd, char **av, char **envp)
{
	if (fdout == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fdout, STDOUT_FILENO) < 0)
		perror_exit("child2");
	if (close(fd[1]) == -1)
		perror_exit("close");
	exec(av[3], envp, av);
	exit(EXIT_FAILURE);
}

static void	child_1(int fdin, int *fd, char **av, char **envp)
{
	if (fdin == -1)
		exit(EXIT_FAILURE);
	if (dup2(fdin, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		perror_exit("child1");
	if (close(fd[0]) == -1)
		perror_exit("close");
	exec(av[2], envp, av);
	exit(EXIT_FAILURE);
}

static int	pipex(int fdin, int fdout, char **av, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	c1pid;
	pid_t	c2pid;

	if (pipe(fd) == -1)
		perror_exit("pipe");
	c1pid = fork();
	if (c1pid < 0)
		perror_exit("fork");
	if (c1pid == 0)
		child_1(fdin, fd, av, envp);
	c2pid = fork();
	if (c2pid < 0)
		perror_exit("fork");
	if (c2pid == 0)
		child_2(fdout, fd, av, envp);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		perror_exit("close");
	waitpid(c1pid, &status, 0);
	waitpid(c2pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int ac, char **av, char **envp)
{
	int	fdin;
	int	fdout;

	if (ac != 5)
	{
		ft_putstr_fd("Need 5 args : ./pipex infile cmd1 cmd2 outfile\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fdin = ft_open(av[1], STDIN_FILENO, av);
	fdout = ft_open(av[4], STDOUT_FILENO, av);
	return (pipex(fdin, fdout, av, envp));
}
