#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 

int main(void)
{
    pid_t pid1;
    pid_t pid2;
    int status;
    int status_code;
    int pipe_zero[2];
    char *cmd1[] = {"cat", NULL};
    int err;

    pipe(pipe_zero);


    pid1 = fork();
    if (pid1 == 0)
    {
        pid2 = fork();
        if ( pid2 == 0 )
        {
        close(pipe_zero[0]);
        dup2(pipe_zero[1], 1);
        close(pipe_zero[1]);
        //execl("/bin/sh", "bin/sh", "-c", "./nopath", "NULL");
        err = execlp("pingx", "pingx", "-c", "1", "googlxxxe.com", NULL);
        //execlp("ping", "ping", "-c", "1", "google.com", NULL);
        //execl("/bin/sh", "bin/sh", "-c", "./nopath", "NULL");
        //execve("/bin/cat", d.cmd1, NULL);
        //execve(d.path_cmd1, d.cmd1, NULL);
        if (err < 0)
            printf("Error -1 in cmd1\n");

        }
        else if (pid2 > 0)
        {
            // wait(&status);
            waitpid(pid2, &status, 0);
            if ( WIFEXITED(status) )
            {
                status_code = WEXITSTATUS(status);       
                if (status_code == 0)
                    printf("Success cmd1!\n");
                else
                    printf("   Exit status of the child pid2 was %d\n", status_code);
            }
            close(pipe_zero[1]);
            dup2(pipe_zero[0], 0);
            close(pipe_zero[1]);
            //execl("/bin/sh", "bin/sh", "-c", "./nopath", "NULL");
            execve("/bin/cat", cmd1, NULL);
        }
    }
    else if (pid1 > 0)
    {
        close(pipe_zero[0]);  //    THIS MUST BE PRESENT IN THE PARENT, OTHERWISE IT HANGS
        close(pipe_zero[1]);

        printf("pid1 > 0:  %d\n", pid1);
        waitpid(pid1, &status, 0);
        if ( WIFEXITED(status) )
        {
            status_code = WEXITSTATUS(status);       
            if (status_code == 0)
                printf("Success cmd2!\n");
            else
                printf("   Exit status of the child pid1 was %d\n", status_code);
        }
    }
    return 0;
}