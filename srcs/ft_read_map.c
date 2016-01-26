#include "wolf3d.h"
#include <stdio.h>

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

static int *ft_stockmap(char *line, t_env *e)
{
	int *l;
	int i;
	char *c;
	
	l = NULL;
	i = 0;
	c = line;
	if ((l = (int*)malloc(sizeof(int) * ft_nb_block_line(line))) == NULL)
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
	e->hmap = i;
	return (l);
}

void	ft_read_map(int fd, t_env *e)
{
	char	*line;
	int		ret;
	int		j;
	
	ret = 0;
	j = 0;
	e->map = NULL;
	if ((e->map = (int**)malloc(100 * sizeof(int*))) == NULL)
		exit (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
			exit(0);
		e->map[j] = ft_stockmap(line, e);
		j++;
	}
	e->lmap = j;
	free(line);
	close(fd);
//	ft_print_map(e);
	ft_creat_env(e);
	
}

void	ft_read(int fd)
{
	t_env *e;
	e = NULL;
	if ((e = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit(0);
	e->lmap = 0;
	e->hmap = 0;
	ft_read_map(fd, e);	
}
