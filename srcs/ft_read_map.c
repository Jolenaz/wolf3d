#include "wolf3d.h"

static int ft_nb_block_line(char *line)
{
	int i;
	char *c;
	
	c = line;
	i = 0;
	while (*c)
	{
		if (*c >= '0' && *c <= '9')
			i++;
		c++;
	}
	return (i);
}

static double *ft_stockmap(char *line)
{
	double *l;
	int i;
	char *c;
	
	l = NULL;
	i = 0;
	c = line;
	if ((l = (double*)malloc(sizeof(double) * ft_nb_block_line(line))) == NULL)
		exit(0);
	while (*c)
	{
		if (*c >= '0' && *c <= '9' )
		{
			l[i] = *c - '0';
			i++;
		}
		c++;
	}
	return (l);
}

void	ft_read_map(int fd)
{
	char *line;
	int ret;
	double **map;
	int j;
	
	ret = 0;
	j = 0;
	map = NULL;
	if ((map = (double**)malloc(100 * sizeof(double*))) == NULL)
		exit (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			exit(0);
		map[j] = ft_stockmap(line);
		j++;
	}
	free(line);
	close(fd);
	ft_creat_env(map);
}


