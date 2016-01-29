/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/01/29 09:48:14 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	ft_modim(t_env *e)
{
	int x;

	x = 0;
	while (x < SIZE_W)
	{
		double camerax = 2 * x /(double)SIZE_W - 1;
		double rayposx = e->xcam;
		double rayposy = e->ycam;
		double raydirx = e->xdir + e->xscreen * camerax;
		double raydiry = e->ydir + e->yscreen * camerax;
		int mapx = (int)rayposx;
		int mapy = (int)rayposy;
	}
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
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	

	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
