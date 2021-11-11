#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <stdio.h> 
# include <errno.h> 
# include <sys/wait.h>
# include "./libft/libft.h"
# include "structs.h"

typedef struct data
{
	pid_t		pid1;
	pid_t		pid2;
	int			pipe_end[2];
	int			fd2;
	int			fd1;
	char		*command1;
	char		*command2;
	char		**cmd1;
	char		**cmd2;
	int			cmd1_is_local;
	int			cmd2_is_local;
	char		*infile;
	char		*outfile;
	char		*envp_path;
	char		*path_cmd1;
	char		*path_cmd2;
	char		**bin_all_paths_cmd1;
	char		**bin_all_paths_cmd2;
}	t_data;

//char **get_command(char *argv);
int	find_paths(char *envp[], t_data *d);
int	append_cmd1_to_all_paths(t_data *d);
int	append_cmd2_to_all_paths(t_data *d);
int	find_correct_path_of_cmd(t_data *d);
int	free_all(t_data *d, int exit_code);
int	init_data_and_get_commands(char *argv[], t_data *d);
int	check_if_local_commands(t_data *d);

#endif