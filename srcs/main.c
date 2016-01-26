#include "wolf3d.h"
#include <stdio.h>

int main(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	ft_read(fd);
	return (0);
}
