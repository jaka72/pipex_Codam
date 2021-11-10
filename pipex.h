#ifndef PIPEX_H
# define PIPEX_H

//#include <string.h>
# include <fcntl.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <stdio.h> 
# include <errno.h> 
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include "./libft/libft.h"
# include "structs.h"

char **get_command(char *argv);
int	find_paths(char *envp[], t_data *d);
int append_cmd1_to_all_paths(t_data *d);
int append_cmd2_to_all_paths(t_data *d);
int find_correct_path_of_cmd(t_data *d);
int	free_all(t_data *d, int exit_code);




#endif