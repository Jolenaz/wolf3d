/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/01 14:37:51 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	put_pixelle(int x, int y, unsigned int *couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = couleur;
	c = (unsigned char*)e->data + x * 4 + y * 4 * SIZE_W;
	*c = *((unsigned char*)ptrc);
	*(c + 1) = *((unsigned char*)ptrc + 1);
	*(c + 2) = *((unsigned char*)ptrc + 2);
	*(c + 3) = *((unsigned char*)ptrc + 3);
}

int		ft_couleur(int wall, int side)
{
	if (wall == 1 || (wall == 13 && side == 0) || (wall == 14 && side == 0))
		return (0x000099);
	else if (wall == 2 || (wall == 23 && side == 0) || (wall == 24 && side == 0))
		return (0xff0000);
	else if (wall == 3 || (wall == 13 && side == 1) || (wall == 23 && side == 1))
		return (0xffff00);
	else if (wall == 4 || (wall == 14 && side == 1) || (wall == 24 && side == 1))
		return (0x66ff00);
	return (0);
}

void	ft_putline(int x, int drawstart, int drawend, int wall, t_env *e, int side)
{
	int y;
	unsigned int couleur;

	y = 0;
	couleur = 0x666666;
	while (y < SIZE_W)
	{
		if (y < drawstart)
			couleur = 0x77b5fe;
		else if (y < drawend)
			couleur = ft_couleur(wall, side);
		else 
			couleur = 0xcccccc;
		put_pixelle(x, y, &couleur, e);
		y++;
	}
}

void	ft_modim(t_env *e)
{
	int x;

	x = 0;
	while (x < SIZE_W)
	{
		double camerax = 2 * x /(double)SIZE_W - 1;
		double rayposx = e->xcam;
		double rayposy = e->ycam;
		double raydirx = e->xdir + e->xscreen * camerax;
		double raydiry = e->ydir + e->yscreen * camerax;
		int mapx = (int)rayposx;
		int mapy = (int)rayposy;
		double sidedistx;
		double sidedisty;
		double deltadistx = sqrt(1 + (raydiry * raydiry) / (raydirx * raydirx));
		double deltadisty = sqrt(1 + (raydirx * raydirx) / (raydiry * raydiry));
		double perpwalldist;
		int stepx;
		int stepy;
		int hit = 0;
		int side;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (rayposx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (1.0 - rayposx + mapx) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (rayposy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (1.0 - rayposy + mapy) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (e->map[mapx][mapy] > 0)
				hit = 1;
		}
		if (side == 0)
			perpwalldist = fabs((mapx - rayposx + (1 - stepx) /2) / raydirx);
		else
			perpwalldist = fabs((mapy - rayposy + (1 - stepy) /2) / raydiry);
		int lineheight = abs((int)(SIZE_W / perpwalldist));
		int drawstart = -lineheight / 2 + SIZE_W / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + SIZE_W / 2;
		if (drawend > SIZE_W)
			drawend = SIZE_W - 1;
		ft_putline(x, drawstart, drawend, e->map[mapx][mapy], e, side);
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
	e->img = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->data = mlx_get_data_addr(e->img, &bpp, &ls, &endian);
	mlx_clear_window(e->mlx, e->win);
	ft_modim(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img2, 50, 50);
	mlx_destroy_image(e->mlx, e->img);
}
int		key_down_hook(int kc, t_env *e)
{
	double movespeed;
	double rotspeed;
	double tmp;

	movespeed = 0.5;
	rotspeed = -0.5;
	if (kc == 13)
	{
		if (e->map[(int)(e->xcam + e->xdir * movespeed)][(int)e->ycam] == 0)
			e->xcam += e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * movespeed)] == 0)
			e->ycam += e->ydir * movespeed;
	}
	if (kc == 1)
	{
		if (e->map[(int)(e->xcam - e->xdir * movespeed)][(int)e->ycam] == 0)
			e->xcam -= e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * movespeed)] == 0)
			e->ycam -= e->ydir * movespeed;
	}
	if (kc == 0)
	{
		if (e->map[(int)(e->xcam - e->xscreen * movespeed)][(int)e->ycam] == 0)
			e->xcam -= e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * movespeed)] == 0)
			e->ycam -= e->yscreen * movespeed;
	}
	if (kc == 2)
	{
		if (e->map[(int)(e->xcam + e->xscreen * movespeed)][(int)e->ycam] == 0)
			e->xcam += e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen + movespeed)] == 0)
			e->ycam += e->yscreen * movespeed;
	}
	if (kc == 123)
	{
		tmp = e->xdir;
		e->xdir = e->xdir * cos(-rotspeed) - e->ydir * sin(-rotspeed);
		e->ydir = tmp * sin(-rotspeed) + e->ydir * cos(-rotspeed);
		tmp = e->xscreen;
		e->xscreen = e->xscreen * cos(-rotspeed) - e->yscreen * sin(-rotspeed);
		e->yscreen = tmp * sin(-rotspeed) + e->yscreen * cos(-rotspeed);
	}
	if (kc == 124)
	{
		tmp = e->xdir;
		e->xdir = e->xdir * cos(rotspeed) - e->ydir * sin(rotspeed);
		e->ydir = tmp * sin(rotspeed) + e->ydir * cos(rotspeed);
		tmp = e->xscreen;
		e->xscreen = e->xscreen * cos(rotspeed) - e->yscreen * sin(rotspeed);
		e->yscreen = tmp * sin(rotspeed) + e->yscreen * cos(rotspeed);
	}
	if (kc == 53)
		exit(0);
	ft_creat_img(e);
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
	int width = 100;
	int height = 96;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->xcam = 15;
	e->ycam = 15;
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	e->img2 = mlx_xpm_file_to_image(e->mlx, "images/im.xpm", &width, &height);

	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
