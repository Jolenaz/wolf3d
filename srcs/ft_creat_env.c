/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/02 16:43:13 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <limits.h>

void	put_pixelle(int x, int y, unsigned int *couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = couleur;
	c = (unsigned char*)e->data[0] + x * 4 + y * 4 * SIZE_W;
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

void	ft_cop_im(int texx, int texy, int x, int y, int wall, t_env *e, int side)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (wall == 1 || (wall == 13 && side == 0) || (wall == 14 && side == 0))
		c = (unsigned char*)e->data[1] + texx * 4 + texy * 4 * SIZE_T + 4 * 25 * SIZE_T;
	else if (wall == 2 || (wall == 23 && side == 0) || (wall == 24 && side == 0))
		c = (unsigned char*)e->data[2] + texx * 4 + texy * 4 * SIZE_T + 4 * 25 * SIZE_T;
	else if (wall == 3 || (wall == 13 && side == 1) || (wall == 23 && side == 1))
		c = (unsigned char*)e->data[3] + texx * 4 + texy * 4 * SIZE_T + 4 * 25 * SIZE_T;
	else if (wall == 4 || (wall == 14 && side == 1) || (wall == 24 && side == 1))
		c = (unsigned char*)e->data[4] + texx * 4 + texy * 4 * SIZE_T + 4 * 25 * SIZE_T;
	else
		c = (unsigned char*)e->data[wall] + texx * 4 + texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (side && wall != 5 && wall != 6)
		*ptrc -= 0x010101;
	put_pixelle(x, y, ptrc, e);
}

void	ft_put_text_line(int x, int texx, int drawstart, int drawend, int wall, t_env *e, int side, int lineheight, double distwall, double floorxwall, double floorywall)
{
	int y;
	double currentdist;

	y = drawend;
	while (y < SIZE_W)
	{
		currentdist =  SIZE_W / (2.0 * y - SIZE_W);
		double weight;
		weight = currentdist / distwall;
		double currentfloorx;
		double currentfloory;
		int floortexx;
		int floortexy;
		currentfloorx = weight * floorxwall + (1.0 - weight) * e->xcam;
		currentfloory = weight * floorywall + (1.0 - weight) * e->ycam;
		floortexx = (int)(currentfloorx * (double)SIZE_T) % SIZE_T;
		floortexy = (int)(currentfloory * (double)SIZE_T) % SIZE_T;
		ft_cop_im(floortexx, floortexy, x, SIZE_W - y, 5, e, side);
		ft_cop_im(floortexx, floortexy, x, y, 6, e, side);
		y++;
	}
	y = drawstart;
	while (y < drawend)
	{
		int d = y * 256 - SIZE_W * 128 + lineheight * 128;
		int texy = ((d * SIZE_T) / lineheight) / 256;
		ft_cop_im(texx, texy, x, y, wall, e, side);
		y++;
	}
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
		int lineheight = (int)(SIZE_W / perpwalldist);
		int drawstart = -lineheight / 2 + SIZE_W / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + SIZE_W / 2;
		if (drawend > SIZE_W)
			drawend = SIZE_W - 1;
		double wallx;
		if (side == 1)
			wallx = rayposx + ((mapy - rayposy + (1 - stepy) / 2) / raydiry) * raydirx;
		else
			wallx = rayposy + ((mapx - rayposx + (1 - stepx) / 2) / raydirx) * raydiry;
		int texx = (int)(wallx * (double)SIZE_T);
		if (side == 0 && raydirx > 0)
			texx = SIZE_T - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = SIZE_T - texx - 1;
		double floorxwall;
		double floorywall;
		if (side == 0 && raydirx > 0)
		{
			floorxwall = (double)mapx;
			floorywall = (double)mapy + wallx;
		}
		else if (side == 0 && raydirx < 0)
		{
			floorxwall = (double)mapx + 1.0;
			floorywall = (double)mapy + wallx;
		}
		else if (side == 1 && raydiry > 0)
		{
			floorxwall = (double)mapx + wallx;
			floorywall = (double)mapy;
		}
		else
		{
			floorxwall = (double)mapx + wallx;
			floorywall = (double)mapy + 1.0;
		}
//		if (drawend < 0)
//			drawend = SIZE_W;
		//	ft_putline(x, drawstart, drawend, e->map[mapx][mapy], e, side);
		ft_put_text_line(x, texx, drawstart, drawend, e->map[mapx][mapy], e, side, lineheight, perpwalldist, floorxwall, floorywall);	
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
	e->data[0] = mlx_get_data_addr(e->img[0], &bpp, &ls, &endian);
	e->data[1] = mlx_get_data_addr(e->img[1], &bpp, &ls, &endian);
	e->data[2] = mlx_get_data_addr(e->img[2], &bpp, &ls, &endian);
	e->data[3] = mlx_get_data_addr(e->img[3], &bpp, &ls, &endian);
	e->data[4] = mlx_get_data_addr(e->img[4], &bpp, &ls, &endian);
	e->data[5] = mlx_get_data_addr(e->img[5], &bpp, &ls, &endian);
	e->data[6] = mlx_get_data_addr(e->img[6], &bpp, &ls, &endian);
	mlx_clear_window(e->mlx, e->win);
	ft_modim(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
	mlx_destroy_image(e->mlx, e->img[0]);
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
		if (e->map[(int)(e->xcam + e->xdir * 1.5 *movespeed)][(int)e->ycam] == 0)
			e->xcam += e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1.5 * movespeed)] == 0)
			e->ycam += e->ydir * movespeed;
	}
	if (kc == 1)
	{
		if (e->map[(int)(e->xcam - e->xdir * 1.5 * movespeed)][(int)e->ycam] == 0)
			e->xcam -= e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1.5 * movespeed)] == 0)
			e->ycam -= e->ydir * movespeed;
	}
	if (kc == 0)
	{
		if (e->map[(int)(e->xcam - e->xscreen * 1.5 * movespeed)][(int)e->ycam] == 0)
			e->xcam -= e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1.5 * movespeed)] == 0)
			e->ycam -= e->yscreen * movespeed;
	}
	if (kc == 2)
	{
		if (e->map[(int)(e->xcam + e->xscreen * 1.5 * movespeed)][(int)e->ycam] == 0)
			e->xcam += e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1.5 * movespeed)] == 0)
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
	int width = 256;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "Wolf 3D");
	e->xcam = 2;
	e->ycam = 2;
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	e->img = (void**)malloc(sizeof(void*) * 7);
	e->data = (char**)malloc(sizeof(char*) * 7);
	e->img[1] = mlx_xpm_file_to_image(e->mlx, "images/im1.xpm", &width, &width);
	e->img[2] = mlx_xpm_file_to_image(e->mlx, "images/im2.xpm", &width, &width);
	e->img[3] = mlx_xpm_file_to_image(e->mlx, "images/im3.xpm", &width, &width);
	e->img[4] = mlx_xpm_file_to_image(e->mlx, "images/im4.xpm", &width, &width);
	e->img[5] = mlx_xpm_file_to_image(e->mlx, "images/im5.xpm", &width, &width);
	e->img[6] = mlx_xpm_file_to_image(e->mlx, "images/im6.xpm", &width, &width);
	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
