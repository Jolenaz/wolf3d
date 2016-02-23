/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_down_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:25:30 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:26:30 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_down_hook(int kc, t_env *e)
{
	double rotspeed;
	double movespeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	mlx_do_key_autorepeatoff(e->mlx);
	if (e->pause == 0)
	{
		if (kc == 13 || kc == 126)
		{
			if (e->map[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam += e->ydir * movespeed;
			e->key13 = 1;
		}
		if (kc == 1 || kc == 125)
		{
			e->key1 = 1;
			if (e->map[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam -= e->ydir * movespeed;
		}
		if (kc == 0)
		{
			e->key0 = 1;
			if (e->map[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam -= e->yscreen * movespeed;
		}
		if (kc == 2)
		{
			e->key2 = 1;
			if (e->map[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam += e->yscreen * movespeed;
		}
		if (kc == 123)
		{
			e->key123 = 1;
			tmp = e->xdir;
			e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
			e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
			e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
		}
		if (kc == 124)
		{
			e->key124 = 1;
			tmp = e->xdir;
			e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
			e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
			e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
		}
	}
	if (kc == 53 && e->pause == 0)
		e->key53 = 1;
	if (kc == 53 && e->pause == 1)
		e->key53 = 0;
	if (e->pause == 0)
		ft_creat_img(e);
	if (kc == 49 && e->vic == 1)
		exit(0);
	return (0);
}

