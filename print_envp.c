#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;


	while (envp[i] != NULL)
	{
//		printf("%s\n", envp[i]);
		if (envp[i][0] == 'P' && envp[i][1] == 'A')
			printf("%s\n", envp[i]);

		i++;
	}
	return (0);
}