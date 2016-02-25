/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:18:42 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 09:56:47 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_mh1(t_env *e)
{
	e->show = 1;
	if ((int)e->xcam == 15 && ((int)e->ycam == 11 || (int)e->ycam == 10) &&
			e->xdir > -0.3 && e->xdir < 0.2 && e->ydir > -1 && e->ydir < -0.9
			&& e->qr == 3)
		e->key49 = 1;
	if ((int)e->xcam == 7 && ((int)e->ycam == 12 || (int)e->ycam == 13) &&
			e->xdir > -0.7 && e->xdir < 0.2 && e->ydir > 0.7 && e->ydir < 1
			&& e->qr == 4)
		e->key49 = 1;
	if ((int)e->xcam == 1 && ((int)e->ycam == 10 || (int)e->ycam == 11) &&
			e->xdir > -0.5 && e->xdir < 0.2 && e->ydir > 0.7 && e->ydir < 1
			&& e->qr == 5)
		e->key49 = 1;
}

static void	ft_mh2(t_env *e)
{
	e->take = 1;
	if (((int)e->xcam == 10 || (int)e->xcam == 11) && (int)e->ycam == 11 &&
			e->xdir < -0.8 && e->xdir > -1 && e->ydir > -0.4 && e->ydir < 0.5)
		e->qr = 3;
	if ((int)e->xcam == 9 && ((int)e->ycam == 8 || (int)e->ycam == 7) &&
			e->xdir < 0.4 && e->xdir > -0.8 && e->ydir > 0.5 && e->ydir < 1)
		e->qr = 4;
	if (((int)e->xcam == 6 || (int)e->xcam == 5) && (int)e->ycam == 22 &&
			e->xdir < -0.8 && e->xdir > -1 && e->ydir > -0.6 && e->ydir < 0.4)
		e->qr = 5;
}

int			mouse_hook(int b, int x, int y, t_env *e)
{
	if (b == 2 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
		ft_mh1(e);
	if (b == 1 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
		ft_mh2(e);
	if (b == 1 && x > 422 && x < 629 && y < 448 && y > 407 &&
			e->pause == 1 && e->help == 0)
		exit(0);
	if (b == 1 && x > 419 && x < 629 && y < 327 && y > 283 &&
			e->pause == 1 && e->help == 0)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[9], 0, 0);
		e->help = 1;
	}
	if (b == 1 && x > 419 && x < 626 && y < 205 && y > 161 &&
			e->pause == 1 && e->help == 0)
		e->key53 = 0;
	if (b == 1 && x > 429 && x < 466 && y < 529 && y > 494 &&
			e->pause == 1 && e->help == 1)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[8], 0, 0);
		e->help = 0;
	}
	return (0);
}
