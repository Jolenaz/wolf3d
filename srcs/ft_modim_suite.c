/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modim_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:03:41 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 17:07:00 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_modim_suite_a(t_ray *ray, t_pict *pict)
{
	pict->lineheight = (int)(SIZE_W / pict->perpwalldist);
	pict->drawstart = -pict->lineheight / 2 + SIZE_W / 2;
	if (pict->drawstart < 0)
		pict->drawstart = 0;
	pict->drawend = pict->lineheight / 2 + SIZE_W / 2;
	if (pict->drawend > SIZE_W)
		pict->drawend = SIZE_W - 1;
	if (pict->side == 1)
		ray->wallx = ray->rayposx + ((ray->mapy - ray->rayposy +
					(1 - ray->stepy) / 2) / ray->raydiry) * ray->raydirx;
	else
		ray->wallx = ray->rayposy + ((ray->mapx - ray->rayposx +
					(1 - ray->stepx) / 2) / ray->raydirx) * ray->raydiry;
	ray->wallx -= floor(ray->wallx);
	pict->texx = (int)(ray->wallx * (double)SIZE_T);
	if (pict->side == 0 && ray->raydirx > 0)
		pict->texx = SIZE_T - pict->texx - 1;
	if (pict->side == 1 && ray->raydiry < 0)
		pict->texx = SIZE_T - pict->texx - 1;
}

void		ft_modim_suite_b(t_ray *ray, t_pict *pict)
{
	if (pict->side == 0 && ray->raydirx > 0)
	{
		pict->floorxwall = (double)(ray->mapx);
		pict->floorywall = (double)(ray->mapy) + ray->wallx;
	}
	else if (pict->side == 0 && ray->raydirx < 0)
	{
		pict->floorxwall = (double)(ray->mapx) + 1.0;
		pict->floorywall = (double)(ray->mapy) + ray->wallx;
	}
	else if (pict->side == 1 && ray->raydiry > 0)
	{
		pict->floorxwall = (double)(ray->mapx) + (ray->wallx);
		pict->floorywall = (double)(ray->mapy);
	}
	else
	{
		pict->floorxwall = (double)(ray->mapx) + (ray->wallx);
		pict->floorywall = (double)(ray->mapy) + 1.0;
	}
}

void		ft_modim_suite(t_env *e, t_ray *ray, t_pict *pict)
{
	int		tmp;

	e->zbuff[pict->x] = pict->perpwalldist;
	ft_modim_suite_a(ray, pict);
	ft_modim_suite_b(ray, pict);
	if (e->keytex == 0)
	{
		pict->tex = e->map[ray->mapx][ray->mapy];
		ft_putline(*pict, e);
	}
	else
	{
		pict->tex = e->map[ray->mapx][ray->mapy];
		ft_put_text_line(*pict, e);
	}
	if (e->map[ray->mapx][ray->mapy] == 1 || (pict->side == 0 &&
				(e->map[ray->mapx][ray->mapy] == 21 ||
				e->map[ray->mapx][ray->mapy] == 12)))
	{
		tmp = pict->drawstart;
		pict->drawstart = 2 * pict->drawstart - pict->drawend;
		pict->drawend = tmp;
		pict->tex = 5;
		ft_put_text_line(*pict, e);
	}
}
