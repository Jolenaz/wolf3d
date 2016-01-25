#include "wolf3d.h"

void	ft_creat_env(double **map)
{
	t_env *e;
	e = NULL;
	if ((e = (t_env*)malloc(sizeof(t_env))) == NULL)
		exit(0);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "wolf3d");
	

}
