/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 09:04:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/19 18:25:21 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

static int *ft_stockmap(char *line, t_env *e)
{
	int *l;
	int i;
	char *c;

	l = NULL;
	i = 0;
	c = line;
	if ((l = (int*)malloc(sizeof(int) * e->hmap)) == NULL)
		exit(0);
	if ((*c >= '0' && *c <= '9') || *c == '-')
	{
		l[i] = atoi(c);
		i++;
		c++;
	}
	while (*c)
	{
		if (((*c >= '0' && *c <= '9') || *c == '-') && *(c - 1) == ' ')
		{
			l[i] = atoi(c);
			i++;
		}
		c++;
	}
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
	e->map2 = NULL;
	e->map3 = NULL;
	line = (char*)malloc(sizeof (char));
	if ((ret = get_next_line(fd, &line)) == -1)
		exit(0);
	e->lmap = ft_atoi(line);
	if ((ret = get_next_line(fd, &line)) == -1)
		exit(0);
	e->hmap = ft_atoi(line);
	if ((ret = get_next_line(fd, &line)) == -1)
		exit(0);
	if ((e->map = (int**)malloc(sizeof(int*) * e->lmap)) == NULL)
		exit(0);
	if ((e->map2 = (int**)malloc(sizeof(int*) * e->lmap)) == NULL)
		exit(0);
	if ((e->map3 = (int**)malloc(sizeof(int*) * e->lmap)) == NULL)
		exit(0);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strlen(line) != 0)
	{
		if (ret == -1)
			exit(0);
		e->map[j] = ft_stockmap(line, e);
		j++;
	}
	j = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strlen(line) != 0)
	{
		if (ret == -1)
			exit(0);
		e->map2[j] = ft_stockmap(line, e);
		j++;
	}	
	j = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strlen(line) != 0)
	{
		if (ret == -1)
			exit(0);
		e->map3[j] = ft_stockmap(line, e);
		j++;
	}
	free(line);
	close(fd);
//	ft_print_map(e);
//	ft_print_map2(e);
//	ft_print_map3(e);
	ft_creat_obj_env(e);
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
