/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_move_hook.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:21:19 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 09:53:39 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_momov1(t_env *e, double rotspeed)
{
	double tmp;

	tmp = e->xdir;
	e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
	e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
	tmp = e->xscreen;
	e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
	e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
}

int			mouse_move_hook(int x, int y, t_env *e)
{
	static int	x0 = 0;
	double		rotspeed;

	rotspeed = 0.1;
	y = 0;
	if (e->pause == 0)
	{
		if ((x0 - x) < 0)
		{
			ft_momov1(e, rotspeed);
			x0 = x;
		}
		if ((x0 - x) > 0)
		{
			ft_momov1(e, -rotspeed);
			x0 = x;
		}
		ft_creat_img(e);
	}
	return (0);
}
