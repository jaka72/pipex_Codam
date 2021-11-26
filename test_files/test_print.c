#include "pipex.h"


int first(void)
{
    int i;

     i = 0;
     i = i + 55;
//     exit(0);
    return (i);
}

int second(void)
{
    int b = first();
    return (b);
}


int main(void)
{
    char *cmd[] = {"xxx","","", NULL};
//    perror("testprint");
    printf("Test, printed from test01.c\n");

    //int a = second();
    //printf("after exit\n");

    //printf("a: %d\n", a);
    //int fd = open("xxx", O_RDONLY);
    //execve("xxx", cmd, NULL);
    //perror("testprint");
    //printf("after exit, fd %d, errno %d\n", fd, errno);

    return (0);
}