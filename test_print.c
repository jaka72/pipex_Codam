#include "pipex.h"


int first(void)
{
    int i;

     i = 0;
     i = i + 55;
     exit(0);
    return (i);
}

int second(void)
{
    int b = first();
    return (b);
}


int main(void)
{
    printf("Test, printet from test01.c\n");

    int a = second();
    printf("after exit\n");

    printf("a: %d\n", a);

    return (0);
}