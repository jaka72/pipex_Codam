#include <stdio.h>
#include <unistd.h>

int main(void)
{

//	char *args[] = {"/usr/bin/ls", "-l", "-a", NULL};
	char *args[] = {"/bin/ls", "-l", "-a", NULL};
//	char *args[] = {"/ls", "-l", "-a", NULL};
	char *env_args[] = { (char*)0 };

	execve(args[0], args, env_args);

  return 1;
}