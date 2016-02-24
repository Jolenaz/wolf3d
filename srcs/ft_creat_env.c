/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:46:51 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <time.h>

int		expose_hook(t_env *e)
{
	static int i = 1;

	if (i)
	{
		i = 0;
		ft_creat_img(e);
	}
	return (0);
}

void	ft_init_data(t_env *e)
{
	t_data	d;
	int		i;

	d.bpp = 4;
	d.ls = 4 * SIZE_W;
	d.endian = 0;
	i = -1;
	while (++i < 26)
	{
		if (i != 12 && i != 21 && i)
			e->data_wall[i] =
				mlx_get_data_addr(e->img_wall[i], &d.bpp, &d.ls, &d.endian);
		if (i < 9 && i != 2 && i)
			e->data_door[i] =
				mlx_get_data_addr(e->img_door[i], &d.bpp, &d.ls, &d.endian);
		if (i > 1 && i < 4)
			e->data_sb[i] =
				mlx_get_data_addr(e->img_sb[i], &d.bpp, &d.ls, &d.endian);
		if (i < 22)
			e->data_floor[i] =
				mlx_get_data_addr(e->img_floor[i], &d.bpp, &d.ls, &d.endian);
		if (i && i < 13)
			e->data_obj[i] =
				mlx_get_data_addr(e->img_obj[i], &d.bpp, &d.ls, &d.endian);
	}
}

void	ft_init_env(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->xcam = 30;
	e->ycam = 11;
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	e->key13 = 0;
	e->key49 = 0;
	e->key53 = 0;
	e->key1 = 0;
	e->dd = 0;
	e->help = 0;
	e->take = 0;
	e->show = 0;
	e->qr = 0;
	e->vic = 0;
	e->key0 = 0;
	e->key2 = 0;
	e->keytex = 1;
	e->pause = 0;
}

void	ft_creat_env(t_env *e)
{
	ft_init_env(e);
	ft_init_malloc(e);
	ft_init_wimg(e);
	ft_init_fimg(e);
	ft_init_dsbimg(e);
	ft_init_oimg(e);
	ft_init_b1_img(e);
	ft_init_b2_img(e);
	ft_init_data(e);
	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_key_up_hook(e->win, key_up_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_mouse_move_hook(e->win, mouse_move_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
