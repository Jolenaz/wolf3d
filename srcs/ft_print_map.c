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
