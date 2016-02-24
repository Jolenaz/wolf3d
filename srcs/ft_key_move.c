/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:54:07 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 16:03:09 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_key_a(t_env *e, double movespeed)
{
	if (e->map[(int)(e->xcam + e->xdir * 1.1
				* movespeed)][(int)e->ycam] <= 0 &&
			e->map3[(int)(e->xcam + e->xdir * 1.1
				* movespeed)][(int)e->ycam] <= 0)
		e->xcam += e->xdir * movespeed;
	if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1
				* movespeed)] <= 0 &&
			e->map3[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1
				* movespeed)] <= 0)
		e->ycam += e->ydir * movespeed;
	e->key13 = 1;
}

void	ft_key_b(t_env *e, double movespeed)
{
	e->key1 = 1;
	if (e->map[(int)(e->xcam - e->xdir * 1.1
				* movespeed)][(int)e->ycam] <= 0 &&
			e->map3[(int)(e->xcam - e->xdir * 1.1
				* movespeed)][(int)e->ycam] <= 0)
		e->xcam -= e->xdir * movespeed;
	if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1
				* movespeed)] <= 0 &&
			e->map3[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1
				* movespeed)] <= 0)
		e->ycam -= e->ydir * movespeed;
}

void	ft_key_c(t_env *e, double movespeed)
{
	e->key0 = 1;
	if (e->map[(int)(e->xcam - e->xscreen * 1.1
				* movespeed)][(int)e->ycam] <= 0 &&
			e->map3[(int)(e->xcam - e->xscreen * 1.1
				* movespeed)][(int)e->ycam] <= 0)
		e->xcam -= e->xscreen * movespeed;
	if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1
				* movespeed)] <= 0 &&
			e->map3[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1
				* movespeed)] <= 0)
		e->ycam -= e->yscreen * movespeed;
}

void	ft_key_d(t_env *e, double movespeed)
{
	e->key2 = 1;
	if (e->map[(int)(e->xcam + e->xscreen * 1.1
				* movespeed)][(int)e->ycam] <= 0 &&
			e->map3[(int)(e->xcam + e->xscreen * 1.1
				* movespeed)][(int)e->ycam] <= 0)
		e->xcam += e->xscreen * movespeed;
	if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1
				* movespeed)] <= 0 &&
			e->map3[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1
				* movespeed)] <= 0)
		e->ycam += e->yscreen * movespeed;
}
