#include "header.h"

int main(int argc, char *argv)
{
	if (mkfifo("myfifo1", 0777) == -1) {
		if (errno != EEXIST) {
			printf("Could not create fifo file\n");
			return (-1);
		}
	}

	int fd = open("myfifo01", O_WRONLY);
	if (fd == -1)
		return (-1);
	int x = 97;
	if (write(fd, &x, sizeof(int)) == -1)
		return (-1);
	close(fd);
	return (0);
}