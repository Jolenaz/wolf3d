/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 21:11:32 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 17:10:01 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_calc_dist(t_env *e)
{
	int i;

	i = 0;
	while (i < e->nbobj)
	{
		e->tabobj[i].dist = hypot((e->xcam - e->tabobj[i].x),
				(e->ycam - e->tabobj[i].y));
		i++;
	}
}

void	ft_swap_obj(t_env *e, int i)
{
	t_obj tmp;

	tmp = e->tabobj[i];
	e->tabobj[i] = e->tabobj[i + 1];
	e->tabobj[i + 1] = tmp;
}

void	ft_sort_obj(t_env *e)
{
	int i;
	int j;
	int rep;

	j = 0;
	rep = 1;
	ft_calc_dist(e);
	while (j < e->nbobj && rep)
	{
		rep = 0;
		i = 0;
		while (i < (e->nbobj - 1))
		{
			if (e->tabobj[i].dist < e->tabobj[i + 1].dist)
			{
				ft_swap_obj(e, i);
				rep = 1;
			}
			i++;
		}
		j++;
	}
}
