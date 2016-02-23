/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 12:02:11 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <time.h>

void	ft_init_ob_im(t_env *e)
{
	unsigned int couleur;
	int x;
	int y;

	couleur = 0xff000000;
	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_W)
		{

			put_pixelle(x, y, &couleur, e);
			y++;
		}
		x++;
	}
}

void	ft_cop_door(t_pict pict, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (pict.tex == 1 || pict.tex == 2)
		c = (unsigned char*)e->data_door[1] + (pict.texx + e->dd) * 4 + pict.texy * 8 * SIZE_T;
	else
		c = (unsigned char*)e->data_door[pict.tex] + (pict.texx + e->dd) * 4 + pict.texy * 8 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (*ptrc != 0xff000000)
		put_pixelle(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_cop_wall(t_pict pict, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (pict.tex == 1 || (pict.tex == 12 && pict.side == 0) || (pict.tex == 21 && pict.side == 0) || (pict.tex == 12 && pict.side == 0))
		c = (unsigned char*)e->data_wall[1] + pict.texx * 4 + pict.texy * 4 * SIZE_T;
	else if (pict.tex == 2 || (pict.tex == 21 && pict.side == 1) || (pict.tex == 12 && pict.side == 1))
		c = (unsigned char*)e->data_wall[2] + pict.texx * 4 + pict.texy * 4 * SIZE_T;
	else
		c = (unsigned char*)e->data_wall[pict.tex] + pict.texx * 4 + pict.texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (pict.side == 0 && (pict.tex == 2 || pict.tex == 3))
		*ptrc -= 0x101010;
	put_pixelle(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_cop_floor(t_flo flo, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_floor[flo.tex] + flo.floortexx * 4 + flo.floortexy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(flo.x, flo.y, ptrc, e);
	free(ptrc);
}

void	ft_put_text_line(t_pict pict, t_env *e)
{
	t_flo	flo;

	pict.y = pict.drawend;
	if (pict.tex != 5)
	{
		while (pict.y < SIZE_W)
		{
			flo.currentdist =  (double)SIZE_W / (2.0 * (double)pict.y - (double)SIZE_W);
			flo.weight = flo.currentdist / pict.perpwalldist;
			flo.currentfloorx = flo.weight * pict.floorxwall + (1.0 - flo.weight) * (double)e->xcam;
			flo.currentfloory = flo.weight * pict.floorywall + (1.0 - flo.weight) * (double)e->ycam;
			flo.floortexx = (int)(flo.currentfloorx * (double)SIZE_T) % SIZE_T;
			flo.floortexy = (int)(flo.currentfloory * (double)SIZE_T) % SIZE_T;
			if(pict.drawend != SIZE_W - 1 && (int)(flo.currentfloorx) < 32 && (int)(flo.currentfloory) < 32) 
			{
				flo.x = pict.x;
				if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] > 0 && e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] < 9 )
				{
					flo.y = SIZE_W - pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] + 1;
					ft_cop_floor(flo, e);
					flo.y = pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)];
					ft_cop_floor(flo, e);
				}
				else if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] == 0)
				{
					flo.tex = 0;
					flo.y = pict.y;
					ft_cop_floor(flo, e);
				}
				else if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] >= 0 )
				{
					flo.y = SIZE_W - pict.y;
					flo.tex = 6;
					ft_cop_floor(flo, e);
					flo.y = pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)];
					ft_cop_floor(flo, e);
				}
			}
			pict.y++;
		}
	}
	pict.y = pict.drawstart;
	while (pict.y < pict.drawend)
	{	
		if (pict.tex != 5)
			pict.d = pict.y * 256 - SIZE_W * 128 + pict.lineheight * 128;
		else 
			pict.d = (pict.y - pict.drawstart) * 256;
		pict.texy = ((pict.d * SIZE_T) / pict.lineheight) / 256;
		ft_cop_wall(pict, e);
		pict.y++;
	}
}

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
		//	ft_put_text_line(pict, e);
		}
		pict.x++;
	}
}

void	ft_init_buff(t_env *e)
{
	int x;

	x = 0;
	while (x < SIZE_W)
	{
		e->zbuff[x] = 0;
		e->zisdoor[x] = 0;
		e->zdoor[x].mapx = 0;
		e->zdoor[x].mapy = 0;
		e->zdoor[x].stepx = 0;
		e->zdoor[x].stepy = 0;
		e->zdoor[x].rayposx = 0;
		e->zdoor[x].rayposy = 0;
		e->zdoor[x].raydirx = 0.0;
		e->zdoor[x].raydiry = 0.0;
		x++;
	}

}

void	ft_creat_img(t_env *e)
{
	int bpp;
	int ls;
	int endian;

	bpp = 4;
	ls = 4 * SIZE_W;
	endian = 0;
	e->img[0] = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->img[1] = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->data[0] = mlx_get_data_addr(e->img[0], &bpp, &ls, &endian);
	e->data[1] = mlx_get_data_addr(e->img[1], &bpp, &ls, &endian);
	ft_init_ob_im(e);
	ft_check_vic(e);
	mlx_clear_window(e->mlx, e->win);
	ft_init_buff(e);
	ft_sort_obj(e);
	ft_put_skybox(e);
	ft_modim(e);
	ft_put_door(e);
	ft_put_obj(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img[1], 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
	if (e->key53)
		ft_move_pause(e);
	else if (e->key53 == 0 && e->pause)
		ft_move_back_pause(e);
	else if (e->take == 1)
		ft_take_pic(e);
	else if (e->show == 1)
		ft_show_pic(e);
	else
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[0], 250, 650);
	if (e->qr)
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[30 + e->qr], 0, 600);

	mlx_destroy_image(e->mlx, e->img[0]);
	mlx_destroy_image(e->mlx, e->img[1]);
}

int		key_down_hook(int kc, t_env *e)
{
	double rotspeed;
	double movespeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	mlx_do_key_autorepeatoff(e->mlx);
	if (e->pause == 0)
	{
		if (kc == 13 || kc == 126)
		{
			if (e->map[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam += e->ydir * movespeed;
			e->key13 = 1;
		}
		if (kc == 1 || kc == 125)
		{
			e->key1 = 1;
			if (e->map[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam -= e->ydir * movespeed;
		}
		if (kc == 0)
		{
			e->key0 = 1;
			if (e->map[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam -= e->yscreen * movespeed;
		}
		if (kc == 2)
		{
			e->key2 = 1;
			if (e->map[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam += e->yscreen * movespeed;
		}
		if (kc == 123)
		{
			e->key123 = 1;
			tmp = e->xdir;
			e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
			e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
			e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
		}
		if (kc == 124)
		{
			e->key124 = 1;
			tmp = e->xdir;
			e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
			e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
			e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
		}
	}
	if (kc == 53 && e->pause == 0)
		e->key53 = 1;
	if (kc == 53 && e->pause == 1)
		e->key53 = 0;
	if (e->pause == 0)
		ft_creat_img(e);
	if (kc == 49 && e->vic == 1)
		exit(0);
	return (0);
}

int		key_up_hook(int kc, t_env *e)
{
	if (kc == 13 || kc == 126)
		e->key13 = 0;
	if (kc == 1 || kc == 125)
		e->key1 = 0;
	if (kc == 0)
		e->key0 = 0;
	if (kc == 2)
		e->key2 = 0;
	if (kc == 123)
		e->key123 = 0;
	if (kc == 124)
		e->key124 = 0;
	if (kc == 17 && e->keytex)
		e->keytex = 0;
	else if (kc == 17)
		e->keytex = 1;	
	return (0);
}

void	ft_open_door(t_env *e)
{
	static int i = 0;

	if (i < 20)
	{
		e->dd += 10;
		i++;
	}
	else
	{
		i = 0;
		e->key49 = 0;
		e->dd = 0;
		if (e->qr == 3)
		{
			e->map[15][8] = 0;
			e->map3[15][9] = -3;
		}
		else if (e->qr == 4)
		{
			e->map[7][15] = 0;
			e->map3[7][14] = -4;
		}
		else if (e->qr == 5)
		{
			e->map[1][13] = 0;
			e->map3[1][12] = -5;
		}
	}

}

int		loop_hook(t_env *e)
{
	//	printf("xdir cam = %f, ydir cam = %f\n",e->xdir, e->ydir);
	double movespeed;
	double rotspeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	if (e->pause == 0)
	{
		if (e->key13)
		{
			if (e->map[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0 && 
					e->map3[(int)(e->xcam + e->xdir * 1.1 *movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam += e->ydir * movespeed;
		}
		if (e->key1)
		{
			if (e->map[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xdir * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xdir * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->ydir * 1.1 * movespeed)] <= 0)
				e->ycam -= e->ydir * movespeed;
		}
		if (e->key0)
		{
			if (e->map[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam - e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam -= e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam -= e->yscreen * movespeed;
		}
		if (e->key2)
		{
			if (e->map[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0 &&
					e->map3[(int)(e->xcam + e->xscreen * 1.1 * movespeed)][(int)e->ycam] <= 0)
				e->xcam += e->xscreen * movespeed;
			if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0 &&
					e->map3[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.1 * movespeed)] <= 0)
				e->ycam += e->yscreen * movespeed;
		}
		if (e->key124)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
			e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
			e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
		}
		if (e->key123)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
			e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
			e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
		}
		if (e->key49)
			ft_open_door(e);
		ft_creat_img(e);
	}
	else if (e->pause == 1 && e->key53 == 0)
		ft_creat_img(e);
	return (0);
}

int		mouse_move_hook(int x, int y, t_env *e)
{
	static int x0 = 0;
	double rotspeed;
	double tmp;

	rotspeed = 0.1;
	//	printf("x = %d, y = %d\n", x, y);
	y = 0;
	if (e->pause == 0)
	{
		if ((x0 - x) < 0)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
			e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
			e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
			x0 = x;
		}
		if ((x0 - x) > 0)
		{
			tmp = e->xdir;
			e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
			e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
			tmp = e->xscreen;
			e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
			e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
			x0 = x;
		}
		ft_creat_img(e);
	}
	return (0);
}

int		mouse_hook(int b, int x, int y, t_env *e)
{
//	printf("xcam = %d, ycam = %d, xdir = %f, ydir = %f\n",(int)e->xcam , (int)e->ycam, e->xdir, e->ydir);
	if (b == 2 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
	{
		e->show = 1;
		if ((int)e->xcam == 15 && ((int)e->ycam == 11 || (int)e->ycam == 10) && e->xdir > -0.3 && e->xdir < 0.2 && e->ydir > -1 && e->ydir < -0.9 && e->qr == 3)
			e->key49 = 1;
		if ((int)e->xcam == 7 && ((int)e->ycam == 12 || (int)e->ycam == 13) && e->xdir > -0.7 && e->xdir < 0.2 && e->ydir > 0.7 && e->ydir < 1 && e->qr == 4)
			e->key49 = 1;
		if ((int)e->xcam == 1 && ((int)e->ycam == 10 || (int)e->ycam == 11) && e->xdir > -0.5 && e->xdir < 0.2 && e->ydir > 0.7 && e->ydir < 1 && e->qr == 5)
			e->key49 = 1;

	}
	if (b == 1 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
	{
		e->take = 1;
		if (((int)e->xcam == 10 || (int)e->xcam == 11) && (int)e->ycam == 11 && e->xdir < -0.8 && e->xdir > -1 && e->ydir > -0.4 && e->ydir < 0.5)
			e->qr = 3;
		if ((int)e->xcam == 9 && ((int)e->ycam == 8 || (int)e->ycam == 7) && e->xdir < 0.4 && e->xdir > -0.8 && e->ydir > 0.5 && e->ydir < 1)
			e->qr = 4;
		if (((int)e->xcam == 6 || (int)e->xcam == 5) && (int)e->ycam == 22 && e->xdir < -0.8 && e->xdir > -1 && e->ydir > -0.6 && e->ydir < 0.4)
			e->qr = 5;
	}

	if (b == 1 && x > 422 && x < 629 && y < 448 && y > 407 && e->pause == 1 && e->help == 0)
		exit(0);
	if (b == 1 && x > 419 && x < 629 && y < 327 && y > 283 && e->pause == 1 && e->help == 0)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[9], 0, 0);
		e->help = 1;
	}
	if (b == 1 && x > 419 && x < 626 && y < 205 && y > 161 && e->pause == 1 && e->help == 0)
		e->key53 = 0;
	if (b == 1 && x > 429 && x < 466 && y < 529 && y > 494 && e->pause == 1 && e->help == 1)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[8], 0, 0);
		e->help = 0;
	}
	return (0);
}

int expose_hook(t_env *e)
{
	static int i = 1;

	if (i)
	{
		i = 0;
		ft_creat_img(e);
	}
	return (0);
}

void	ft_creat_env(t_env *e)
{
	int bpp;
	int ls;
	int endian;
	int width = 256;

	bpp = 4;
	ls = 4 * SIZE_W;
	endian = 0;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->xcam = 25;
	e->ycam = 25;
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	e->key13 = 0;
	e->key49 = 0;
	e->key53 = 0;
	e->key1 = 0;
	e->dd = 0;
	e->help = 0;
	e->take = 0;
	e->show = 0;
	e->qr = 0;
	e->vic = 0;
	e->key0 = 0;
	e->key2 = 0;
	e->keytex = 1;
	e->pause = 0;
	e->img_wall = (void**)malloc(sizeof(void*) * 101);
	e->img_door = (void**)malloc(sizeof(void*) * 101);
	e->img_bras = (void**)malloc(sizeof(void*) * 101);
	e->img = (void**)malloc(sizeof(void*) * 101);
	e->img_sb = (void**)malloc(sizeof(void*) * 101);
	e->img_floor = (void**)malloc(sizeof(void*) * 101);
	e->img_obj = (void**)malloc(sizeof(void*) * 101);
	e->data_wall = (char**)malloc(sizeof(char*) * 101);
	e->data_door = (char**)malloc(sizeof(char*) * 101);
	e->data_bras = (char**)malloc(sizeof(char*) * 101);
	e->data = (char**)malloc(sizeof(char*) * 101);
	e->data_sb = (char**)malloc(sizeof(char*) * 101);
	e->data_floor = (char**)malloc(sizeof(char*) * 101);
	e->data_obj = (char**)malloc(sizeof(char*) * 101);
	e->img_wall[1] = mlx_xpm_file_to_image(e->mlx, "images/wall1.xpm", &width, &width);
	e->img_wall[2] = mlx_xpm_file_to_image(e->mlx, "images/wall2.xpm", &width, &width);
	e->img_wall[3] = mlx_xpm_file_to_image(e->mlx, "images/wall3.xpm", &width, &width);
	e->img_wall[4] = mlx_xpm_file_to_image(e->mlx, "images/wall4.xpm", &width, &width);
	e->img_wall[5] = mlx_xpm_file_to_image(e->mlx, "images/wall5.xpm", &width, &width);
	e->img_wall[6] = mlx_xpm_file_to_image(e->mlx, "images/wall6.xpm", &width, &width);
	e->img_wall[7] = mlx_xpm_file_to_image(e->mlx, "images/wall7.xpm", &width, &width);
	e->img_wall[8] = mlx_xpm_file_to_image(e->mlx, "images/wall8.xpm", &width, &width);
	e->img_wall[9] = mlx_xpm_file_to_image(e->mlx, "images/wall9.xpm", &width, &width);
	e->img_wall[10] = mlx_xpm_file_to_image(e->mlx, "images/wall10.xpm", &width, &width);
	e->img_wall[11] = mlx_xpm_file_to_image(e->mlx, "images/wall11.xpm", &width, &width);
	e->img_wall[14] = mlx_xpm_file_to_image(e->mlx, "images/wall14.xpm", &width, &width);
	e->img_wall[13] = mlx_xpm_file_to_image(e->mlx, "images/wall13.xpm", &width, &width);
	e->img_wall[15] = mlx_xpm_file_to_image(e->mlx, "images/wall15.xpm", &width, &width);
	e->img_wall[16] = mlx_xpm_file_to_image(e->mlx, "images/wall16.xpm", &width, &width);
	e->img_wall[17] = mlx_xpm_file_to_image(e->mlx, "images/wall17.xpm", &width, &width);
	e->img_wall[18] = mlx_xpm_file_to_image(e->mlx, "images/wall18.xpm", &width, &width);
	e->img_wall[19] = mlx_xpm_file_to_image(e->mlx, "images/wall19.xpm", &width, &width);
	e->img_wall[20] = mlx_xpm_file_to_image(e->mlx, "images/wall20.xpm", &width, &width);
	e->img_wall[22] = mlx_xpm_file_to_image(e->mlx, "images/wall22.xpm", &width, &width);
	e->img_wall[23] = mlx_xpm_file_to_image(e->mlx, "images/wall23.xpm", &width, &width);
	e->img_wall[24] = mlx_xpm_file_to_image(e->mlx, "images/wall24.xpm", &width, &width);
	e->img_door[1] = mlx_xpm_file_to_image(e->mlx, "images/door1.xpm", &width, &width);
	e->img_door[3] = mlx_xpm_file_to_image(e->mlx, "images/door3.xpm", &width, &width);
	e->img_door[4] = mlx_xpm_file_to_image(e->mlx, "images/door4.xpm", &width, &width);
	e->img_door[5] = mlx_xpm_file_to_image(e->mlx, "images/door5.xpm", &width, &width);
	e->img_door[6] = mlx_xpm_file_to_image(e->mlx, "images/door6.xpm", &width, &width);
	e->img_door[7] = mlx_xpm_file_to_image(e->mlx, "images/door7.xpm", &width, &width);
	e->img_door[8] = mlx_xpm_file_to_image(e->mlx, "images/door8.xpm", &width, &width);
	e->img_floor[1] = mlx_xpm_file_to_image(e->mlx, "images/floor1.xpm", &width, &width);
	e->img_floor[2] = mlx_xpm_file_to_image(e->mlx, "images/floor2.xpm", &width, &width);
	e->img_floor[3] = mlx_xpm_file_to_image(e->mlx, "images/floor3.xpm", &width, &width);
	e->img_floor[4] = mlx_xpm_file_to_image(e->mlx, "images/floor4.xpm", &width, &width);
	e->img_floor[5] = mlx_xpm_file_to_image(e->mlx, "images/floor5.xpm", &width, &width);
	e->img_floor[6] = mlx_xpm_file_to_image(e->mlx, "images/floor6.xpm", &width, &width);
	e->img_floor[7] = mlx_xpm_file_to_image(e->mlx, "images/floor7.xpm", &width, &width);
	e->img_floor[8] = mlx_xpm_file_to_image(e->mlx, "images/floor8.xpm", &width, &width);
	e->img_floor[9] = mlx_xpm_file_to_image(e->mlx, "images/floor9.xpm", &width, &width);
	e->img_floor[10] = mlx_xpm_file_to_image(e->mlx, "images/floor10.xpm", &width, &width);
	e->img_floor[11] = mlx_xpm_file_to_image(e->mlx, "images/floor11.xpm", &width, &width);
	e->img_floor[12] = mlx_xpm_file_to_image(e->mlx, "images/floor12.xpm", &width, &width);
	e->img_floor[13] = mlx_xpm_file_to_image(e->mlx, "images/floor13.xpm", &width, &width);
	e->img_floor[14] = mlx_xpm_file_to_image(e->mlx, "images/floor14.xpm", &width, &width);
	e->img_floor[15] = mlx_xpm_file_to_image(e->mlx, "images/floor15.xpm", &width, &width);
	e->img_floor[16] = mlx_xpm_file_to_image(e->mlx, "images/floor16.xpm", &width, &width);
	e->img_floor[17] = mlx_xpm_file_to_image(e->mlx, "images/floor17.xpm", &width, &width);
	e->img_floor[18] = mlx_xpm_file_to_image(e->mlx, "images/floor18.xpm", &width, &width);
	e->img_floor[19] = mlx_xpm_file_to_image(e->mlx, "images/floor19.xpm", &width, &width);
	e->img_floor[20] = mlx_xpm_file_to_image(e->mlx, "images/floor20.xpm", &width, &width);
	e->img_floor[0] = mlx_xpm_file_to_image(e->mlx, "images/floor0.xpm", &width, &width);
	e->img_sb[2] = mlx_xpm_file_to_image(e->mlx, "images/sb2.xpm", &width, &width);
	e->img_sb[3] = mlx_xpm_file_to_image(e->mlx, "images/sb3.xpm", &width, &width);
	e->img_obj[1] = mlx_xpm_file_to_image(e->mlx, "images/obj1.xpm", &width, &width);
	e->img_obj[2] = mlx_xpm_file_to_image(e->mlx, "images/obj2.xpm", &width, &width);
	e->img_obj[3] = mlx_xpm_file_to_image(e->mlx, "images/obj3.xpm", &width, &width);
	e->img_obj[4] = mlx_xpm_file_to_image(e->mlx, "images/obj4.xpm", &width, &width);
	e->img_obj[5] = mlx_xpm_file_to_image(e->mlx, "images/obj5.xpm", &width, &width);
	e->img_obj[6] = mlx_xpm_file_to_image(e->mlx, "images/obj6.xpm", &width, &width);
	e->img_obj[7] = mlx_xpm_file_to_image(e->mlx, "images/obj7.xpm", &width, &width);
	e->img_obj[8] = mlx_xpm_file_to_image(e->mlx, "images/obj8.xpm", &width, &width);
	e->img_obj[9] = mlx_xpm_file_to_image(e->mlx, "images/obj9.xpm", &width, &width);
	e->img_obj[10] = mlx_xpm_file_to_image(e->mlx, "images/obj10.xpm", &width, &width);
	e->img_obj[11] = mlx_xpm_file_to_image(e->mlx, "images/obj11.xpm", &width, &width);
	e->img_obj[12] = mlx_xpm_file_to_image(e->mlx, "images/obj12.xpm", &width, &width);
	e->img_bras[0] = mlx_xpm_file_to_image(e->mlx, "images/bras.xpm", &width, &width);
	e->img_bras[1] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_1.xpm", &width, &width);
	e->img_bras[2] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_2.xpm", &width, &width);
	e->img_bras[3] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_3.xpm", &width, &width);
	e->img_bras[4] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_4.xpm", &width, &width);
	e->img_bras[5] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_5.xpm", &width, &width);
	e->img_bras[6] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_6.xpm", &width, &width);
	e->img_bras[7] = mlx_xpm_file_to_image(e->mlx, "images/menu_vide.xpm", &width, &width);
	e->img_bras[8] = mlx_xpm_file_to_image(e->mlx, "images/menu_menu.xpm", &width, &width);
	e->img_bras[9] = mlx_xpm_file_to_image(e->mlx, "images/menu_help.xpm", &width, &width);
	e->img_bras[10] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_1.xpm", &width, &width);
	e->img_bras[11] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_2.xpm", &width, &width);
	e->img_bras[12] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_3.xpm", &width, &width);
	e->img_bras[13] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_4.xpm", &width, &width);
	e->img_bras[14] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_5.xpm", &width, &width);
	e->img_bras[15] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_6.xpm", &width, &width);
	e->img_bras[16] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_6.xpm", &width, &width);
	e->img_bras[17] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_1.xpm", &width, &width);
	e->img_bras[18] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_2.xpm", &width, &width);
	e->img_bras[19] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_3.xpm", &width, &width);
	e->img_bras[20] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_4.xpm", &width, &width);
	e->img_bras[21] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_5.xpm", &width, &width);
	e->img_bras[22] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_6.xpm", &width, &width);
	e->img_bras[23] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_7.xpm", &width, &width);
	e->img_bras[33] = mlx_xpm_file_to_image(e->mlx, "images/bras3.xpm", &width, &width);
	e->img_bras[34] = mlx_xpm_file_to_image(e->mlx, "images/bras4.xpm", &width, &width);
	e->img_bras[35] = mlx_xpm_file_to_image(e->mlx, "images/bras5.xpm", &width, &width);
	e->data_wall[1] = mlx_get_data_addr(e->img_wall[1], &bpp, &ls, &endian);
	e->data_wall[2] = mlx_get_data_addr(e->img_wall[2], &bpp, &ls, &endian);
	e->data_wall[3] = mlx_get_data_addr(e->img_wall[3], &bpp, &ls, &endian);
	e->data_wall[4] = mlx_get_data_addr(e->img_wall[4], &bpp, &ls, &endian);
	e->data_wall[5] = mlx_get_data_addr(e->img_wall[5], &bpp, &ls, &endian);
	e->data_wall[6] = mlx_get_data_addr(e->img_wall[6], &bpp, &ls, &endian);
	e->data_wall[7] = mlx_get_data_addr(e->img_wall[7], &bpp, &ls, &endian);
	e->data_wall[8] = mlx_get_data_addr(e->img_wall[8], &bpp, &ls, &endian);
	e->data_wall[9] = mlx_get_data_addr(e->img_wall[9], &bpp, &ls, &endian);
	e->data_wall[10] = mlx_get_data_addr(e->img_wall[10], &bpp, &ls, &endian);
	e->data_wall[11] = mlx_get_data_addr(e->img_wall[11], &bpp, &ls, &endian);
	e->data_wall[14] = mlx_get_data_addr(e->img_wall[14], &bpp, &ls, &endian);
	e->data_wall[13] = mlx_get_data_addr(e->img_wall[13], &bpp, &ls, &endian);
	e->data_wall[15] = mlx_get_data_addr(e->img_wall[15], &bpp, &ls, &endian);
	e->data_wall[16] = mlx_get_data_addr(e->img_wall[16], &bpp, &ls, &endian);
	e->data_wall[17] = mlx_get_data_addr(e->img_wall[17], &bpp, &ls, &endian);
	e->data_wall[18] = mlx_get_data_addr(e->img_wall[18], &bpp, &ls, &endian);
	e->data_wall[19] = mlx_get_data_addr(e->img_wall[19], &bpp, &ls, &endian);
	e->data_wall[20] = mlx_get_data_addr(e->img_wall[20], &bpp, &ls, &endian);
	e->data_wall[22] = mlx_get_data_addr(e->img_wall[22], &bpp, &ls, &endian);
	e->data_wall[23] = mlx_get_data_addr(e->img_wall[23], &bpp, &ls, &endian);
	e->data_wall[24] = mlx_get_data_addr(e->img_wall[24], &bpp, &ls, &endian);
	e->data_door[1] = mlx_get_data_addr(e->img_door[1], &bpp, &ls, &endian);
	e->data_door[3] = mlx_get_data_addr(e->img_door[3], &bpp, &ls, &endian);
	e->data_door[4] = mlx_get_data_addr(e->img_door[4], &bpp, &ls, &endian);
	e->data_door[5] = mlx_get_data_addr(e->img_door[5], &bpp, &ls, &endian);
	e->data_door[6] = mlx_get_data_addr(e->img_door[6], &bpp, &ls, &endian);
	e->data_door[7] = mlx_get_data_addr(e->img_door[7], &bpp, &ls, &endian);
	e->data_door[8] = mlx_get_data_addr(e->img_door[8], &bpp, &ls, &endian);
	e->data_sb[2] = mlx_get_data_addr(e->img_sb[2], &bpp, &ls, &endian);
	e->data_sb[3] = mlx_get_data_addr(e->img_sb[3], &bpp, &ls, &endian);
	e->data_floor[1] = mlx_get_data_addr(e->img_floor[1], &bpp, &ls, &endian);
	e->data_floor[2] = mlx_get_data_addr(e->img_floor[2], &bpp, &ls, &endian);
	e->data_floor[3] = mlx_get_data_addr(e->img_floor[3], &bpp, &ls, &endian);
	e->data_floor[4] = mlx_get_data_addr(e->img_floor[4], &bpp, &ls, &endian);
	e->data_floor[5] = mlx_get_data_addr(e->img_floor[5], &bpp, &ls, &endian);
	e->data_floor[6] = mlx_get_data_addr(e->img_floor[6], &bpp, &ls, &endian);
	e->data_floor[7] = mlx_get_data_addr(e->img_floor[7], &bpp, &ls, &endian);
	e->data_floor[8] = mlx_get_data_addr(e->img_floor[8], &bpp, &ls, &endian);
	e->data_floor[9] = mlx_get_data_addr(e->img_floor[9], &bpp, &ls, &endian);
	e->data_floor[10] = mlx_get_data_addr(e->img_floor[10], &bpp, &ls, &endian);
	e->data_floor[11] = mlx_get_data_addr(e->img_floor[11], &bpp, &ls, &endian);
	e->data_floor[12] = mlx_get_data_addr(e->img_floor[12], &bpp, &ls, &endian);
	e->data_floor[13] = mlx_get_data_addr(e->img_floor[13], &bpp, &ls, &endian);
	e->data_floor[14] = mlx_get_data_addr(e->img_floor[14], &bpp, &ls, &endian);
	e->data_floor[15] = mlx_get_data_addr(e->img_floor[15], &bpp, &ls, &endian);
	e->data_floor[16] = mlx_get_data_addr(e->img_floor[16], &bpp, &ls, &endian);
	e->data_floor[17] = mlx_get_data_addr(e->img_floor[17], &bpp, &ls, &endian);
	e->data_floor[18] = mlx_get_data_addr(e->img_floor[18], &bpp, &ls, &endian);
	e->data_floor[19] = mlx_get_data_addr(e->img_floor[19], &bpp, &ls, &endian);
	e->data_floor[20] = mlx_get_data_addr(e->img_floor[20], &bpp, &ls, &endian);
	e->data_floor[0] = mlx_get_data_addr(e->img_floor[0], &bpp, &ls, &endian);
	e->data_obj[1] = mlx_get_data_addr(e->img_obj[1], &bpp, &ls, &endian);
	e->data_obj[2] = mlx_get_data_addr(e->img_obj[2], &bpp, &ls, &endian);
	e->data_obj[3] = mlx_get_data_addr(e->img_obj[3], &bpp, &ls, &endian);
	e->data_obj[4] = mlx_get_data_addr(e->img_obj[4], &bpp, &ls, &endian);
	e->data_obj[5] = mlx_get_data_addr(e->img_obj[5], &bpp, &ls, &endian);
	e->data_obj[6] = mlx_get_data_addr(e->img_obj[6], &bpp, &ls, &endian);
	e->data_obj[7] = mlx_get_data_addr(e->img_obj[7], &bpp, &ls, &endian);
	e->data_obj[8] = mlx_get_data_addr(e->img_obj[8], &bpp, &ls, &endian);
	e->data_obj[9] = mlx_get_data_addr(e->img_obj[9], &bpp, &ls, &endian);
	e->data_obj[10] = mlx_get_data_addr(e->img_obj[10], &bpp, &ls, &endian);
	e->data_obj[11] = mlx_get_data_addr(e->img_obj[11], &bpp, &ls, &endian);
	e->data_obj[12] = mlx_get_data_addr(e->img_obj[12], &bpp, &ls, &endian);
	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_key_up_hook(e->win, key_up_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_mouse_move_hook(e->win, mouse_move_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
