/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:33:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 16:14:42 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_key1(t_env *e, double movespeed)
{
	if (e->key13)
		ft_key_a(e, movespeed);
	if (e->key1)
		ft_key_b(e, movespeed);
}

static void	ft_key2(t_env *e, double movespeed)
{
	if (e->key0)
		ft_key_c(e, movespeed);
	if (e->key2)
		ft_key_d(e, movespeed);
}

static void	ft_key3(t_env *e, double rotspeed)
{
	double tmp;

	if (e->key123)
	{
		tmp = e->xdir;
		e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
		e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
		tmp = e->xscreen;
		e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
		e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
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
}

int			loop_hook(t_env *e)
{
	double movespeed;
	double rotspeed;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	if (e->pause == 0)
	{
		if (e->key13 || e->key1)
			ft_key1(e, movespeed);
		if (e->key0 || e->key2)
			ft_key2(e, movespeed);
		if (e->key123 || e->key124)
			ft_key3(e, rotspeed);
		if (e->key49)
			ft_open_door(e);
		ft_creat_img(e);
	}
	else if (e->pause == 1 && e->key53 == 0)
		ft_creat_img(e);
	return (0);
}
