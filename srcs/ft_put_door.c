/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:37:22 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 10:30:13 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_put_door_line(t_pict pict, t_env *e)
{
	int d;

	pict.y = pict.drawstart;
	while (pict.y < pict.drawend)
	{
		d = pict.y * 256 - SIZE_W * 128 + pict.lineheight * 128;
		pict.texy = ((d * SIZE_T) / pict.lineheight) / 256;
		ft_cop_door(pict, e);
		pict.y++;
	}
}

static void	ft_door2(t_env *e, t_pict *pict)
{
	double wallx;

	if (e->zdoor[pict->x].side == 1)
		wallx = e->zdoor[pict->x].rayposx + ((e->zdoor[pict->x].mapy -
					e->zdoor[pict->x].rayposy + (1 - e->zdoor[pict->x].stepy) /
					2) / e->zdoor[pict->x].raydiry) * e->zdoor[pict->x].raydirx;
	else
		wallx = e->zdoor[pict->x].rayposy + ((e->zdoor[pict->x].mapx -
					e->zdoor[pict->x].rayposx + (1 - e->zdoor[pict->x].stepx) /
					2) / e->zdoor[pict->x].raydirx) * e->zdoor[pict->x].raydiry;
	wallx -= floor(wallx);
	pict->texx = (int)(wallx * (double)SIZE_T);
}

static void	ft_door1(t_env *e, t_pict *pict)
{
	if (e->zdoor[pict->x].side == 0)
		pict->perpwalldist = fabs((e->zdoor[pict->x].mapx -
					e->zdoor[pict->x].rayposx + (1 - e->zdoor[pict->x].stepx)
					/ 2) / e->zdoor[pict->x].raydirx);
	else
		pict->perpwalldist = fabs((e->zdoor[pict->x].mapy -
					e->zdoor[pict->x].rayposy + (1 - e->zdoor[pict->x].stepy)
					/ 2) / e->zdoor[pict->x].raydiry);
	e->zbuff[pict->x] = pict->perpwalldist;
	pict->lineheight = (int)(SIZE_W / pict->perpwalldist);
	pict->drawstart = -pict->lineheight / 2 + SIZE_W / 2;
	if (pict->drawstart < 0)
		pict->drawstart = 0;
	pict->drawend = pict->lineheight / 2 + SIZE_W / 2;
	if (pict->drawend > SIZE_W)
		pict->drawend = SIZE_W - 1;
	ft_door2(e, pict);
}

void		ft_put_door(t_env *e)
{
	t_pict	pict;

	pict.x = 0;
	while (pict.x < SIZE_W)
	{
		if (e->zisdoor[pict.x])
		{
			ft_door1(e, &pict);
			ft_put_door2(e, &pict);
		}
		pict.x++;
	}
}
