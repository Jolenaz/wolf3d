/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_door2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 10:15:41 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 10:32:47 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_door1(t_env *e, t_pict *pict)
{
	if (e->zdoor[pict->x].side == 0 && e->zdoor[pict->x].raydirx > 0)
	{
		pict->tex = abs(e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy]);
		ft_put_door_line(*pict, e);
	}
	else
	{
		pict->tex = abs(e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy])
			+ 1;
		ft_put_door_line(*pict, e);
	}
}

static void	ft_door2(t_env *e, t_pict *pict)
{
	pict->tex = abs(e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy]);
	if ((e->map2[(int)e->xcam][(int)e->ycam] == 0 ||
				e->map2[(int)e->xcam][(int)e->ycam] == 21) &&
			e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy] == -1)
		ft_put_door_line(*pict, e);
	else if (e->map2[(int)e->xcam][(int)e->ycam] == 1 &&
			e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy] == -2)
		ft_put_door_line(*pict, e);
	else if (e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy] <= -3)
		ft_put_door_line(*pict, e);
}

void		ft_put_door2(t_env *e, t_pict *pict)
{
	int tmp;

	if (e->zdoor[pict->x].side == 0 && e->zdoor[pict->x].raydirx > 0)
		pict->texx = SIZE_T - pict->texx - 1;
	if (e->zdoor[pict->x].side == 1 && e->zdoor[pict->x].raydiry < 0)
		pict->texx = SIZE_T - pict->texx - 1;
	if (abs(e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy]) == 7 &&
			e->keytex == 1)
		ft_door1(e, pict);
	else if (e->keytex == 1)
		ft_door2(e, pict);
	if (e->map[e->zdoor[pict->x].mapx][e->zdoor[pict->x].mapy] == -1 &&
			e->xdir < 0.5)
	{
		tmp = pict->drawstart;
		pict->drawstart = 2 * pict->drawstart - pict->drawend;
		pict->drawend = tmp;
		pict->tex = 5;
		ft_put_text_line(*pict, e);
	}
}
