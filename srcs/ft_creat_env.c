/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/01/27 15:30:59 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
/*
double	ft_dist_wall(double de, t_env *e, unsigned int *couleur)
{
	int x = 0;
	int y = 0;
	double d[2];

	if (cos(de + e->tcam) != 0 )
	{
		while (x < e->lmap && e->map[x + 1][(int)((e->xcam - x) / tan(de + e->tcam) + e->ycam)] == 0)
		{
			x++;
			d[0] = hypot((double)x, ((e->xcam - x) / tan(de + e->tcam) + e->ycam));
		}
		while (y < e->hmap && e->map[(int)((e->ycam - y) / tan(de + e->tcam) + e->xcam)][y] == 0)
		{
			y++;
			d[1] = hypot((double)y, ((e->ycam - y) / tan(de + e->tcam) + e->xcam));
		}
	}
	printf("%f, %f\n", d[0],d[1]);
	*couleur = 0;
	return (d[0]);
}
*/
void	ft_modim(t_env *e)
{
	double de;
	double z = 0;
	int i = 0;
	//unsigned int couleur;

	de = -60. / 180 * M_PI / 2;
	while (de < 60 / 180 * M_PI / 2)
	{
	//	z = ft_dist_wall(de, e, &couleur);
		//ft_put_wall(z, i, e, couleur);
		printf("____%f_____\n",de);
		de = de + 60 / 180 * M_PI / 10;
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
	e->xcam = 3;
	e->ycam = 3;
	e->tcam = 0;

	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
