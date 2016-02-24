/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:44:58 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 17:04:31 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_modim_a(t_env *e, t_ray *ray, t_pict *pict)
{
	ray->camerax = 2 * pict->x / (double)SIZE_W - 1;
	ray->rayposx = e->xcam;
	ray->rayposy = e->ycam;
	ray->raydirx = e->xdir + e->xscreen * ray->camerax;
	ray->raydiry = e->ydir + e->yscreen * ray->camerax;
	ray->mapx = (int)(ray->rayposx);
	ray->mapy = (int)(ray->rayposy);
	ray->deltadistx = sqrt(1 + (ray->raydiry * ray->raydiry) /
			(ray->raydirx * ray->raydirx));
	ray->deltadisty = sqrt(1 + (ray->raydirx * ray->raydirx) /
			(ray->raydiry * ray->raydiry));
}

static void	ft_modim_b(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->rayposx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (1.0 - ray->rayposx + ray->mapx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->rayposy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (1.0 - ray->rayposy + ray->mapy) * ray->deltadisty;
	}
}

void		ft_stock_zbuff(t_env *e, t_ray *ray, t_pict *pict)
{
	e->zisdoor[pict->x] = 1;
	e->zdoor[pict->x].mapx = ray->mapx;
	e->zdoor[pict->x].mapy = ray->mapy;
	e->zdoor[pict->x].stepx = ray->stepx;
	e->zdoor[pict->x].stepy = ray->stepy;
	e->zdoor[pict->x].rayposx = ray->rayposx;
	e->zdoor[pict->x].rayposy = ray->rayposy;
	e->zdoor[pict->x].raydirx = ray->raydirx;
	e->zdoor[pict->x].raydiry = ray->raydiry;
	e->zdoor[pict->x].side = pict->side;
}

int			ft_modim_c(t_env *e, t_ray *ray, t_pict *pict)
{
	if (ray->sidedistx < ray->sidedisty)
	{
		ray->sidedistx += ray->deltadistx;
		ray->mapx += ray->stepx;
		pict->side = 0;
	}
	else
	{
		ray->sidedisty += ray->deltadisty;
		ray->mapy += ray->stepy;
		pict->side = 1;
	}
	if (e->map[ray->mapx][ray->mapy] > 0)
		return (1);
	else if (e->map[ray->mapx][ray->mapy] <= -1)
		ft_stock_zbuff(e, ray, pict);
	return (0);
}

void		ft_modim(t_env *e)
{
	t_pict	pict;
	t_ray	ray;
	int		hit;

	pict.x = 0;
	while (pict.x < SIZE_W)
	{
		hit = 0;
		ft_modim_a(e, &ray, &pict);
		ft_modim_b(&ray);
		while (hit == 0)
		{
			hit = ft_modim_c(e, &ray, &pict);
		}
		if (pict.side == 0)
			pict.perpwalldist = fabs((ray.mapx - ray.rayposx +
						(1 - ray.stepx) / 2) / ray.raydirx);
		else
			pict.perpwalldist = fabs((ray.mapy - ray.rayposy +
						(1 - ray.stepy) / 2) / ray.raydiry);
		ft_modim_suite(e, &ray, &pict);
		pict.x++;
	}
}
