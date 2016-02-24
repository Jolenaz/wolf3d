/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:44:58 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:25:08 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_modim(t_env *e)
{
	t_pict	pict;
	t_ray	ray;
	int		hit;
	int tmp;

	pict.x = 0;
	while (pict.x < SIZE_W)
	{
		hit = 0;
		ray.camerax = 2 * pict.x /(double)SIZE_W - 1;
		ray.rayposx = e->xcam;
		ray.rayposy = e->ycam;
		ray.raydirx = e->xdir + e->xscreen * ray.camerax;
		ray.raydiry = e->ydir + e->yscreen * ray.camerax;
		ray.mapx = (int)(ray.rayposx);
		ray.mapy = (int)(ray.rayposy);
		ray.deltadistx = sqrt(1 + (ray.raydiry * ray.raydiry) / (ray.raydirx * ray.raydirx));
		ray.deltadisty = sqrt(1 + (ray.raydirx * ray.raydirx) / (ray.raydiry * ray.raydiry));
		if (ray.raydirx < 0)
		{
			ray.stepx = -1;
			ray.sidedistx = (ray.rayposx - ray.mapx) * ray.deltadistx;
		}
		else
		{
			ray.stepx = 1;
			ray.sidedistx = (1.0 - ray.rayposx + ray.mapx) * ray.deltadistx;
		}
		if (ray.raydiry < 0)
		{
			ray.stepy = -1;
			ray.sidedisty = (ray.rayposy - ray.mapy) * ray.deltadisty;
		}
		else
		{
			ray.stepy = 1;
			ray.sidedisty = (1.0 - ray.rayposy + ray.mapy) * ray.deltadisty;
		}
		while (hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapx += ray.stepx;
				pict.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapy += ray.stepy;
				pict.side = 1;
			}
			if (e->map[ray.mapx][ray.mapy] > 0)
				hit = 1;
			else if (e->map[ray.mapx][ray.mapy] <= -1)
			{
				e->zisdoor[pict.x] = 1;
				e->zdoor[pict.x].mapx = ray.mapx;
				e->zdoor[pict.x].mapy = ray.mapy;
				e->zdoor[pict.x].stepx = ray.stepx;
				e->zdoor[pict.x].stepy = ray.stepy;
				e->zdoor[pict.x].rayposx = ray.rayposx;
				e->zdoor[pict.x].rayposy = ray.rayposy;
				e->zdoor[pict.x].raydirx = ray.raydirx;
				e->zdoor[pict.x].raydiry = ray.raydiry;
				e->zdoor[pict.x].side = pict.side;
			}
		}
		if (pict.side == 0)
			pict.perpwalldist = fabs((ray.mapx - ray.rayposx + (1 - ray.stepx) /2) / ray.raydirx);
		else
			pict.perpwalldist = fabs((ray.mapy - ray.rayposy + (1 - ray.stepy) /2) / ray.raydiry);
		e->zbuff[pict.x] = pict.perpwalldist;
		pict.lineheight = (int)(SIZE_W / pict.perpwalldist);
		pict.drawstart = -pict.lineheight / 2 + SIZE_W / 2;
		if (pict.drawstart < 0)
			pict.drawstart = 0;
		pict.drawend = pict.lineheight / 2 + SIZE_W / 2;
		if (pict.drawend > SIZE_W)
			pict.drawend = SIZE_W - 1;
		if (pict.side == 1)
			ray.wallx = ray.rayposx + ((ray.mapy - ray.rayposy + (1 - ray.stepy) / 2) / ray.raydiry) * ray.raydirx;
		else
			ray.wallx = ray.rayposy + ((ray.mapx - ray.rayposx + (1 - ray.stepx) / 2) / ray.raydirx) * ray.raydiry;
		ray.wallx -= floor(ray.wallx);
		pict.texx = (int)(ray.wallx * (double)SIZE_T);
		if (pict.side == 0 && ray.raydirx > 0)
			pict.texx = SIZE_T - pict.texx - 1;
		if (pict.side == 1 && ray.raydiry < 0)
			pict.texx = SIZE_T - pict.texx - 1;
		if (pict.side == 0 && ray.raydirx > 0)
		{
			pict.floorxwall = (double)(ray.mapx);
			pict.floorywall = (double)(ray.mapy) + ray.wallx;
		}
		else if (pict.side == 0 && ray.raydirx < 0)
		{
			pict.floorxwall = (double)(ray.mapx) + 1.0;
			pict.floorywall = (double)(ray.mapy) + ray.wallx;
		}
		else if (pict.side == 1 && ray.raydiry > 0)
		{
			pict.floorxwall = (double)(ray.mapx) + (ray.wallx);
			pict.floorywall = (double)(ray.mapy);
		}
		else
		{
			pict.floorxwall = (double)(ray.mapx) + (ray.wallx);
			pict.floorywall = (double)(ray.mapy) + 1.0;
		}
		if (e->keytex == 0)
		{
			pict.tex = e->map[ray.mapx][ray.mapy];
			ft_putline(pict, e);
		}
		else
		{
			pict.tex = e->map[ray.mapx][ray.mapy];
			ft_put_text_line(pict, e);
		}
		if (e->map[ray.mapx][ray.mapy] == 1 || (pict.side == 0 && (e->map[ray.mapx][ray.mapy] == 21 || e->map[ray.mapx][ray.mapy] == 12)))
		{
			tmp = pict.drawstart;
			pict.drawstart = 2 * pict.drawstart - pict.drawend;
			pict.drawend = tmp;
			pict.tex = 5;
			ft_put_text_line(pict, e);
		}
		pict.x++;
	}
}

