/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/01/27 17:09:07 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

double	ft_dist_wall(double de, t_env *e, unsigned int *couleur)
{
	int x[2];
	int y[2];
	double d[2] = {0,0};

	y[0] = 0;
	y[1] = 0;
	x[0] = 0;
	x[1] = 0;
	printf("angle = %d\n", (int)((de + e->tcam) / M_PI * 180));
	if (cos(de + e->tcam) != 0 )
	{
		while (x[0] < e->lmap && (y[0] = (int)((x[0] - e->xcam) / tan(de + e->tcam) + e->ycam)) >= 0 && e->map[x[0]][y[0]] == 0)
		{
			d[0] = hypot((double)x[0], (double)y[0]);
			x[0]++;
		}
		while (y[1] < e->hmap && (x[1] = (int)((y[1] - e->ycam) * tan(de + e->tcam) + e->xcam)) >= 0 && e->map[x[1]][y[1]] == 0)
		{
			d[1] = hypot((double)x[1], (double)y[1]);
			y[1]++;
		}
	}
	printf("%d, %d\n", e->map[x[0]][y[0]], e->map[x[1]][y[1]]);
	*couleur = 0;
	return (d[0]);
}

void	ft_modim(t_env *e)
{
	double de;
	double z = 0;
	int i = 0;
	unsigned int couleur;

	de = -60. / 180 * M_PI / 2;
	while (de <= 60. / 180 * M_PI / 2)
	{
		z = ft_dist_wall(de, e, &couleur);
		//ft_put_wall(z, i, e, couleur);
	//	printf("____%f__%d___\n",de,i);
		de = de + 60. / 180 * M_PI / 6;
		i++;
	}
	if (e->tcam !=0)
		exit(0);
}

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
	ft_modim(e);
	printf("xcam = %f, ycam = %f\n", e->xcam, e->ycam);
	return (0);
}

int expose_hook(t_env *e)
{
	static int i = 1;
	
	if (i)
	{
		i = 0;
		ft_modim(e);
	}
	return (0);
}

void	ft_creat_env(t_env *e)
{
	int bpp;
	int ls;
	int endian;

	bpp = 4;
	ls = 4 * SIZE_W;
	endian = 0;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->img = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->data = mlx_get_data_addr(e->img, &bpp, &ls, &endian);
	e->xcam = 8;
	e->ycam = 3;
	e->tcam = 0;

	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
