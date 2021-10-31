/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:09:21 by tjensen           #+#    #+#             */
/*   Updated: 2021/10/21 19:51:30 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipex_child_set_pipes(int i, int *fd, int **pipes, int childs);
static int	pipex_child_heredoc(char *limiter, int pipe_w, int cmd_count);

pid_t	*pipex_create_child(int childs, char *argv[], bool here_doc)
{
	int		i;
	pid_t	*pid;
	int		**pipes;

	pipes = pipex_pipes_array_get(childs - 1);
	pid = malloc(childs * sizeof(pid_t));
	if (pid == NULL)
		exit(ENOMEM);
	i = 0;
	while (i < childs)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			ft_free((void **)&pid);
			pipex_child(childs, i, pipes, argv);
		}
		if (here_doc)
			waitpid(pid[0], NULL, 0);
		i++;
	}
	pipex_pipes_close(pipes, childs, -1);
	pipex_pipes_array_destroy(pipes, childs - 1);
	return (pid);
}

void	pipex_child(int childs, int i, int **pipes, char **argv)
{
	int		rt;
	int		fd[2];

	rt = pipex_pipes_close(pipes, childs, i);
	pipex_child_set_pipes(i, fd, pipes, childs);
	if (i == 0)
		fd[0] = pipex_open(argv[1], O_RDONLY, 0);
	else if (i == childs - 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		fd[1] = pipex_open(argv[childs + 2], O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (i == childs - 1)
		fd[1] = pipex_open(argv[childs + 2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd[0] == 0 && fd[1] > 0)
		rt = pipex_child_heredoc(argv[2], fd[1], childs - 1);
	else if (fd[0] > 0 && fd[1] > 0)
		rt = pipex_child_execute(fd[0], fd[1], argv[i + 2]);
	else if (rt == EXIT_SUCCESS)
		rt = EXIT_FAILURE;
	pipex_pipes_array_destroy(pipes, childs - 1);
	exit(rt);
}

static void	pipex_child_set_pipes(int i, int *fd, int **pipes, int childs)
{
	if (i > 0)
		fd[0] = pipes[i - 1][0];
	if (i != childs - 1)
		fd[1] = pipes[i][1];
}

static int	pipex_child_heredoc(char *limiter, int pipe_w, int cmd_count)
{
	int		i;
	char	*read;
	char	*limiter_with_nl;

	limiter_with_nl = ft_strjoin(limiter, "\n");
	while (1)
	{
		i = cmd_count - 1;
		while (i)
		{
			write(2, "pipe ", 5);
			i--;
		}
		write(2, "heredoc> ", 9);
		read = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(read, limiter_with_nl, ft_strlen(limiter) + 1))
			break ;
		write(pipe_w, read, ft_strlen(read));
		ft_free((void **)&read);
	}
	close(pipe_w);
	ft_free((void **)&read);
	return (EXIT_SUCCESS);
}

int	pipex_child_execute(int pipe_r, int pipe_w, char *cmd_str)
{
	int			status;
	char		**cmd;
	extern char	**environ;

	cmd = pipex_cmd_get(cmd_str, &status);
	if (cmd == NULL)
		return (status);
	dup2(pipe_r, STDIN_FILENO);
	close(pipe_r);
	dup2(pipe_w, STDOUT_FILENO);
	close(pipe_w);
	execve(cmd[0], cmd, environ);
	pipex_print_error("pipex", strerror(errno), cmd[0]);
	ft_free_split(cmd);
	return (EXIT_FAILURE);
}
