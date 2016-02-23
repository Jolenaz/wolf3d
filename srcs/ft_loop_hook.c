/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:33:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:47:24 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		loop_hook(t_env *e)
{
	//	printf("xdir cam = %f, ydir cam = %f\n",e->xdir, e->ydir);
	double movespeed;
	double rotspeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	if (e->pause == 0)
	{
		if (e->key13)
		{
			if (e->map[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0 && 
					e->map3[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam += e->ydir * movespeed;
		}
		if (e->key1)
		{
			if (e->map[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam -= e->ydir * movespeed;
		}
		if (e->key0)
		{
			if (e->map[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam -= e->yscreen * movespeed;
		}
		if (e->key2)
		{
			if (e->map[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam += e->yscreen * movespeed;
		}
		if (e->key124)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
			e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
			e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
		}
		if (e->key123)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
			e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
			e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
		}
		if (e->key49)
			ft_open_door(e);
		ft_creat_img(e);
	}
	else if (e->pause == 1 && e->key53 == 0)
		ft_creat_img(e);
	return (0);
}

