/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_obj_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 20:42:50 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/15 09:14:07 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_tabobj(t_env *e)
{
	int		i;
	int 	j;
	int 	l;

	i = 0;
	l = 0;
	while (i < e->lmap)
	{
		j = 0;
		while (j < e->hmap)
		{
			if (e->map2[i][j] != 0)
			{
				e->tabobj[l].x = i;
				e->tabobj[l].y = j;
				e->tabobj[l].dist = -1;
				e->tabobj[l].type = abs(e->map3[i][j]);
				l++;
			}
			j++;
		}
		i++;
	}
}

int		ft_nb_obj(t_env *e)
{
	int	i;
	int j;
	int	l;

	i = 0;
	l = 0;
	while (i < e->lmap)
	{
		j = 0;
		while (j < e->hmap)
		{
			if (e->map3[i][j] != 0)
				l++;
			j++;
		}
		i++;
	}
	return (l);
}

void	ft_creat_obj_env(t_env *e)
{
	e->nbobj = ft_nb_obj(e);
	e->tabobj = (t_obj*)malloc(sizeof(t_obj) * e->nbobj);
	ft_init_tabobj(e);
//	ft_print_tabobj(e);
}
