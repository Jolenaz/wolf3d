#include "wolf3d.h"
#include <stdio.h>

void	ft_print_map(t_env *e)
{
	int i = 0;
	int j;
	
	printf("lmap = %d, hmap = %d\n", e->lmap, e->hmap);
	while (i < e->lmap)
	{
		j = 0;
		while (j < e->hmap)
		{
			printf(" %d", e->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_print_map2(t_env *e)
{
	int i = 0;
	int j;
	
	printf("lmap = %d, hmap = %d\n", e->lmap, e->hmap);
	while (i < e->lmap)
	{
		j = 0;
		while (j < e->hmap)
		{
			printf(" %d", e->map2[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_print_map3(t_env *e)
{
	int i = 0;
	int j;
	
	printf("lmap = %d, hmap = %d\n", e->lmap, e->hmap);
	while (i < e->lmap)
	{
		j = 0;
		while (j < e->hmap)
		{
			printf(" %d", e->map3[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_print_tabobj(t_env *e)
{
	int i;

	i = 0;
	while (i < e->nbobj)
	{
		printf("map[%d][%d] = %d, dist = %f\n", e->tabobj[i].x, e->tabobj[i].y, e->tabobj[i].type, e->tabobj[i].dist);
		i++;
	}
	printf("\n");
}
