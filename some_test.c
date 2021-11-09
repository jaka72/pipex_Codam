#include "pipex.h"


int main(void)
{
	char **arr;

	char *str = "abcd/efg/ho/jklm/nopr/stu/vz/wyq";
	
	arr = ft_split(str, '/');

	int i = 0;
	while (arr[i])
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
//	free(arr);

	return (0);
}