#include <fcntl.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h> 

int main(void)
{
	int c;
	char buffer[1];

	printf("This comes from redirection\n");

	c = read(1, buffer, 1);



	printf(" [%c] \n", buffer[0]);

	return (0);
}