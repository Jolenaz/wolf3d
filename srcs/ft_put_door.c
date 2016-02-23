/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:37:22 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:38:58 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_door_line(t_pict pict, t_env *e)
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

void	ft_put_door(t_env *e)
{
	t_pict pict;
	double wallx;
	int tmp;

	pict.x = 0;
	while (pict.x < SIZE_W)
	{
		if (e->zisdoor[pict.x])
		{
			if (e->zdoor[pict.x].side == 0)
				pict.perpwalldist = fabs((e->zdoor[pict.x].mapx - e->zdoor[pict.x].rayposx + (1 - e->zdoor[pict.x].stepx) / 2) / e->zdoor[pict.x].raydirx);
			else
				pict.perpwalldist = fabs((e->zdoor[pict.x].mapy - e->zdoor[pict.x].rayposy + (1 - e->zdoor[pict.x].stepy) / 2) / e->zdoor[pict.x].raydiry);
			e->zbuff[pict.x] = pict.perpwalldist;
			pict.lineheight = (int)(SIZE_W / pict.perpwalldist);
			pict.drawstart = -pict.lineheight / 2 + SIZE_W / 2;
			if (pict.drawstart < 0)
				pict.drawstart = 0;
			pict.drawend = pict.lineheight / 2 + SIZE_W / 2;
			if (pict.drawend > SIZE_W)
				pict.drawend = SIZE_W - 1;
			if (e->zdoor[pict.x].side == 1)
				wallx = e->zdoor[pict.x].rayposx + ((e->zdoor[pict.x].mapy - e->zdoor[pict.x].rayposy + (1 - e->zdoor[pict.x].stepy) / 2) / e->zdoor[pict.x].raydiry) * e->zdoor[pict.x].raydirx;
			else
				wallx = e->zdoor[pict.x].rayposy + ((e->zdoor[pict.x].mapx - e->zdoor[pict.x].rayposx + (1 - e->zdoor[pict.x].stepx) / 2) / e->zdoor[pict.x].raydirx) * e->zdoor[pict.x].raydiry;
			wallx -= floor(wallx);
			pict.texx = (int)(wallx * (double)SIZE_T);
			if (e->zdoor[pict.x].side == 0 && e->zdoor[pict.x].raydirx > 0)
				pict.texx = SIZE_T - pict.texx - 1;
			if (e->zdoor[pict.x].side == 1 && e->zdoor[pict.x].raydiry < 0)
				pict.texx = SIZE_T - pict.texx - 1;
			if (abs(e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy]) == 7 && e->keytex == 1)
			{
				if (e->zdoor[pict.x].side == 0 && e->zdoor[pict.x].raydirx > 0)
				{
					pict.tex = abs(e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy]);
					ft_put_door_line(pict, e);
				}
				else
				{
					pict.tex = abs(e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy]) + 1;
					ft_put_door_line(pict, e);
				}
			}
			else if (e->keytex == 1)
			{
				pict.tex = abs(e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy]);
				if (e->map2[(int)e->xcam][(int)e->ycam] == 0 && e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy] == -1)
					ft_put_door_line(pict, e);
				else if (e->map2[(int)e->xcam][(int)e->ycam] == 1 && e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy] == -2)
					ft_put_door_line(pict, e);
				else if (e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy] <= -3)
					ft_put_door_line(pict, e);
			}
			if (e->map[e->zdoor[pict.x].mapx][e->zdoor[pict.x].mapy] == -1 && e->xdir < 0.5)
			{
				tmp = pict.drawstart;
				pict.drawstart = 2 * pict.drawstart - pict.drawend;
				pict.drawend = tmp;
				pict.tex = 5;
				ft_put_text_line(pict, e);
			}
		}
		pict.x++;
	}
}

