#include "wolf3d.h"
#include <stdio.h>

int		key_hook(int kc, t_env *e)
{
	printf("%d\n",kc);
	if (kc == 126 && e->map[(int)e->xcam][(int)e->ycam - 1] == 0)
		e->ycam -= 0.5;
	if (kc == 125 && e->map[(int)e->xcam][(int)(e->ycam + 0.5)] == 0)
		e->ycam += 0.5;
	if (kc == 123 && e->map[(int)e->xcam - 1][(int)e->ycam] == 0)
		e->xcam -= 0.5;
	if (kc == 124 && e->map[(int)(e->xcam + 0.5)][(int)e->ycam] == 0)
		e->xcam += 0.5;
	if (kc == 53)
		exit(0);
	printf("xcam = %f, ycam = %f\n", e->xcam, e->ycam);
	return (0);
}

void	ft_creat_env(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->xcam = 3;
	e->ycam = 3;
	mlx_key_hook(e->win, key_hook, e);
	mlx_loop(e->mlx);
}
