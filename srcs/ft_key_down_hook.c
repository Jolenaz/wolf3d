/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_down_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:25:30 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 16:05:16 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_key1(t_env *e, double movespeed, int kc)
{
	if (kc == 13 || kc == 126)
		ft_key_a(e, movespeed);
	if (kc == 1 || kc == 125)
		ft_key_b(e, movespeed);
}

static void	ft_key2(t_env *e, double movespeed, int kc)
{
	if (kc == 0)
		ft_key_c(e, movespeed);
	if (kc == 2)
		ft_key_d(e, movespeed);
}

static void	ft_key3(t_env *e, double rotspeed, int kc)
{
	double tmp;

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

int			key_down_hook(int kc, t_env *e)
{
	double rotspeed;
	double movespeed;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	mlx_do_key_autorepeatoff(e->mlx);
	if (e->pause == 0)
	{
		if (kc == 13 || kc == 126 || kc == 1 || kc == 125)
			ft_key1(e, movespeed, kc);
		if (kc == 0 || kc == 2)
			ft_key2(e, movespeed, kc);
		if (kc == 123 || kc == 124)
			ft_key3(e, rotspeed, kc);
	}
	if (kc == 53 && e->pause == 0)
		e->key53 = 1;
	if (kc == 53 && e->pause == 1 && e->help == 0)
		e->key53 = 0;
	if (e->pause == 0)
		ft_creat_img(e);
	if (kc == 49 && e->vic == 1)
		exit(0);
	return (0);
}
