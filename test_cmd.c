#include "pipex.h"


/*
    EXECVE
    The array: The 1st element is the path, including the command 
                name. Other elements are just options.
*/

int main(void)
{
    char *cmd[] = {"./test_print", "", NULL};
//    char *cmd[] = {"/bin/cat", "-e", "infile", NULL};

    execve(cmd[0], cmd, NULL);

    return (0);
}