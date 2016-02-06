/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/06 22:50:33 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

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

void	put_pixelle_door(int x, int y, unsigned int *couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = couleur;
	c = (unsigned char*)e->data[100] + x * 4 + y * 4 * SIZE_W;
	*c = *((unsigned char*)ptrc);
	*(c + 1) = *((unsigned char*)ptrc + 1);
	*(c + 2) = *((unsigned char*)ptrc + 2);
	*(c + 3) = *((unsigned char*)ptrc + 3);
}

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

			put_pixelle_door(x, y, &couleur, e);
			y++;
		}
		x++;
	}
}


int		ft_couleur(int wall, int side)
{
	if (wall == 1 || (wall == 12 && side == 0) || (wall == 21 && side == 0) || (wall == 12 && side == 0))
		return (0x000099);
	else if (wall == 2 || (wall == 23 && side == 1) || (wall == 21 && side == 1) || (wall == 12 && side == 1))
		return (0xff0000);
	else if (wall == 3 || (wall == 23 && side == 0))
		return (0xffff00);
	else if (wall == 4)
		return (0x66ff00);
	return (0);
}

void	ft_cop_door(int texx, int texy, int x, int y, int wall, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (wall == -2)
		c = NULL;
	c = (unsigned char*)e->data[9] + texx * 4 + texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle_door(x, y, ptrc, e);
}

void	ft_cop_im(int texx, int texy, int x, int y, int wall, t_env *e, int side)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (wall == 1 || (wall == 12 && side == 0) || (wall == 21 && side == 0) || (wall == 12 && side == 0))
		c = (unsigned char*)e->data[1] + texx * 4 + texy * 4 * SIZE_T;
	if (wall == 2 || (wall == 23 && side == 1) || (wall == 21 && side == 1) || (wall == 12 && side == 1))
		c = (unsigned char*)e->data[2] + texx * 4 + texy * 4 * SIZE_T;
	if (wall == 3 || (wall == 23 && side == 0))
		c = (unsigned char*)e->data[3] + texx * 4 + texy * 4 * SIZE_T;
	if (wall == 4)
		c = (unsigned char*)e->data[4] + texx * 4 + texy * 4 * SIZE_T;
	if(wall == 5 || wall == 6 || wall == 7)
		c = (unsigned char*)e->data[wall] + texx * 4 + texy * 4 * SIZE_T;
	if(wall == 8)
		c = (unsigned char*)e->data[wall] + texx * 4 + texy * 4 * 3000;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(x, y, ptrc, e);
}

void	ft_put_text_line(int x, int texx, int drawstart, int drawend, int wall, t_env *e, int side, int lineheight, double distwall, double floorxwall, double floorywall)
{
	int y;
	double currentdist;

	y = drawend;
	while (y < SIZE_W)
	{
		currentdist =  (double)SIZE_W / (2.0 * (double)y - (double)SIZE_W);
		double weight;
		weight = currentdist / distwall;
		double currentfloorx;
		double currentfloory;
		int floortexx;
		int floortexy;
		currentfloorx = weight * floorxwall + (1.0 - weight) * (double)e->xcam;
		currentfloory = weight * floorywall + (1.0 - weight) * (double)e->ycam;
		floortexx = (int)(currentfloorx * (double)SIZE_T) % SIZE_T;
		floortexy = (int)(currentfloory * (double)SIZE_T) % SIZE_T;
		if (e->map[(int)currentfloorx][(int)currentfloory] != -1)
		{
			ft_cop_im(floortexx, floortexy, x, SIZE_W - y, 5, e, side);
			ft_cop_im(floortexx, floortexy, x, y, 6, e, side);
		}
		else 
			ft_cop_im(floortexx, floortexy, x, y, 7, e, side);
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

void	ft_put_door_line(int x, int texx, int drawstart, int drawend, int obj, t_env *e, int lineheight)
{
	int y;

	y = drawstart;
	while (y < drawend)
	{
		int d = y * 256 - SIZE_W * 128 + lineheight * 128;
		int texy = ((d * SIZE_T) / lineheight) / 256;
		ft_cop_door(texx, texy, x, y, obj, e);
		y++;
	}
}

void	ft_put_door(int x, t_env *e)
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
		if (e->map[mapx][mapy] < -1)
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
	wallx -= floor(wallx);
	int texx = (int)(wallx * (double)SIZE_T);
	if (side == 0 && raydirx > 0)
		texx = SIZE_T - texx - 1;
	if (side == 1 && raydiry < 0)
		texx = SIZE_T - texx - 1;
	if (e->keytex == 1)
		ft_put_door_line(x, texx, drawstart, drawend, e->map[mapx][mapy], e, lineheight);
}

void	ft_modim(t_env *e)
{
	int x;
	int rep;

	x = 0;
	while (x < SIZE_W)
	{
		rep = 0;
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
			else if (e->map[mapx][mapy] < -1)
				rep = 1;
		}
		if (side == 0)
			perpwalldist = fabs((mapx - rayposx + (1 - stepx) /2) / raydirx);
		else
			perpwalldist = fabs((mapy - rayposy + (1 - stepy) /2) / raydiry);
		e->zbuff[x] = perpwalldist;
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
		wallx -= floor(wallx);
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
		if (e->keytex == 0)
			ft_putline(x, drawstart, drawend, e->map[mapx][mapy], e, side);
		else
			ft_put_text_line(x, texx, drawstart, drawend, e->map[mapx][mapy], e, side, lineheight, perpwalldist, floorxwall, floorywall);
		if (rep)
			ft_put_door(x, e);
		x++;
	}
}

void	ft_put_skybox(t_env *e)
{
	int x;
	int texx;
	int y;

	x = 0;
	while (x < SIZE_W)
	{
		texx = x + (int)(atan2(e->xdir, e->ydir) / M_PI * 3000) + 3000;
		y = 0;
		while (y < 500)
		{
			ft_cop_im(texx, y, x, y, 8, e, 0);
			y++;
		}
		x++;
	}
}

void	ft_put_obj(t_env *e)
{
	int i;

	i = 0;
	while (i < e->nbobj)
	{
		double xobj = e->tabobj[i].x - e->xcam;
		double yobj = e->tabobj[i].y - e->y:cam;
		double invdev = 1.0 / (e->xscreen * e->ydir - e->xdir * e->yscreen);
		double transformx = invdev * (e->ydir * xobj - e->xdir * yobj);
		double transformy = invdev * (-e->yscreen * xobj + e->xscreen yobj);
		int xscreenobj = (int)((SIZE_W / 2) * (1 + transformx / transformey));
		int objheight = abs((int)(SIZE_W / transformy));
		int drawstarty = -objheight / 2 + SIZE_W / 2;
		if (drawstarty < 0)
			drawstarty= 0;
		int drawendy = objheight / 2 + SIZE_W / 2;
		if (drawendy > SIZE_W)
			drawendy = SIZE_W - 1;
		int objwidth = abs((int)(SIZE_W / transformy));
		int drawstartx = -objwidth / 2 + xscreenobj;
		if (drewastartx < 0)
			drawstartx = 0;
		int drawendx = objwidth / 2 + xscreenobj;
		if (drawendx > SIZE_W)
			drawendx = SIZE_W - 1;
		int x = drawstartx;
		int y;
		int texx;
		int texy;
		while (x < drawendx)
		{
			y = drawstarty;
			texx = (int)(256 * (x - (-objwidth / 2 + xscreenobj)) * SIZE_O / objwidth) / 256;
			if (transformy > 0 && x > 0 && x < SIZE_W && transformy < e->zbuff[x])
			{
				while (y < drawendy)
				{
					int d = y * 256 - SIZE_W * 128 + objheight * 128;
					texy = ((d * SIZE_O) / objheight) / 256;
					ft_cop_im(texx, texy, x, y, e->tabobj[i].type, e, 0);
					y++;
				}
			}
			x++;
		}
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
	e->img[50] = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->img[100] = mlx_new_image(e->mlx, SIZE_W, SIZE_W);
	e->data[0] = mlx_get_data_addr(e->img[0], &bpp, &ls, &endian);
	e->data[50] = mlx_get_data_addr(e->img[50], &bpp, &ls, &endian);
	e->data[100] = mlx_get_data_addr(e->img[100], &bpp, &ls, &endian);
	e->data[1] = mlx_get_data_addr(e->img[1], &bpp, &ls, &endian);
	e->data[2] = mlx_get_data_addr(e->img[2], &bpp, &ls, &endian);
	e->data[3] = mlx_get_data_addr(e->img[3], &bpp, &ls, &endian);
	e->data[4] = mlx_get_data_addr(e->img[4], &bpp, &ls, &endian);
	e->data[5] = mlx_get_data_addr(e->img[5], &bpp, &ls, &endian);
	e->data[6] = mlx_get_data_addr(e->img[6], &bpp, &ls, &endian);
	e->data[7] = mlx_get_data_addr(e->img[7], &bpp, &ls, &endian);
	e->data[8] = mlx_get_data_addr(e->img[8], &bpp, &ls, &endian);
	e->data[9] = mlx_get_data_addr(e->img[9], &bpp, &ls, &endian);
	e->data[10] = mlx_get_data_addr(e->img[10], &bpp, &ls, &endian);
	mlx_clear_window(e->mlx, e->win);
	ft_init_ob_im(e);
	ft_sort_obj(e);
	ft_put_skybox(e);
	ft_modim(e);
	ft_put_obj(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img[100], 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img[50], 0, 0);
	mlx_destroy_image(e->mlx, e->img[0]);
	mlx_destroy_image(e->mlx, e->img[50]);
}


int		key_down_hook(int kc, t_env *e)
{
	double rotspeed;
	double movespeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	mlx_do_key_autorepeatoff(e->mlx);
	if (kc == 13 || kc == 126)
	{
		if (e->map[(int)(e->xcam + e->xdir * 1 *movespeed)][(int)e->ycam] <= 0)
			e->xcam += e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1 * movespeed)] <= 0)
			e->ycam += e->ydir * movespeed;
		e->key13 = 1;
	}
	if (kc == 1 || kc == 125)
	{
		e->key1 = 1;
		if (e->map[(int)(e->xcam - e->xdir * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam -= e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1 * movespeed)] <= 0)
			e->ycam -= e->ydir * movespeed;
	}
	if (kc == 0)
	{
		e->key0 = 1;
		if (e->map[(int)(e->xcam - e->xscreen * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam -= e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1 * movespeed)] <= 0)
			e->ycam -= e->yscreen * movespeed;
	}
	if (kc == 2)
	{
		e->key2 = 1;
		if (e->map[(int)(e->xcam + e->xscreen * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam += e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1 * movespeed)] <= 0)
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
	if (kc == 53)
		exit(0);
	ft_creat_img(e);
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

int		loop_hook(t_env *e)
{
	double movespeed;
	double rotspeed;
	double tmp;

	rotspeed = 10.0 / 180.0 * M_PI;
	movespeed = 0.5;
	if (e->key13)
	{
		if (e->map[(int)(e->xcam + e->xdir * 1 *movespeed)][(int)e->ycam] <= 0)
			e->xcam += e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->ydir * 1 * movespeed)] <= 0)
			e->ycam += e->ydir * movespeed;
	}
	if (e->key1)
	{
		if (e->map[(int)(e->xcam - e->xdir * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam -= e->xdir * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->ydir * 1 * movespeed)] <= 0)
			e->ycam -= e->ydir * movespeed;
	}
	if (e->key0)
	{
		if (e->map[(int)(e->xcam - e->xscreen * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam -= e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam - e->yscreen * 1 * movespeed)] <= 0)
			e->ycam -= e->yscreen * movespeed;
	}
	if (e->key2)
	{
		if (e->map[(int)(e->xcam + e->xscreen * 1 * movespeed)][(int)e->ycam] <= 0)
			e->xcam += e->xscreen * movespeed;
		if (e->map[(int)e->xcam][(int)(e->ycam + e->yscreen * 1 * movespeed)] <= 0)
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
	ft_creat_img(e);
	return (0);
}

int		mouse_move_hook(int x, int y, t_env *e)
{
	static int x0 = 0;
	double rotspeed;
	double tmp;

	rotspeed = 0.3;
	y = 0;
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
	e->xcam = 23;
	e->ycam = 13;
	e->xdir = -1;
	e->ydir = 0;
	e->xscreen = 0;
	e->yscreen = 0.66;
	e->key13 = 0;
	e->key1 = 0;
	e->key0 = 0;
	e->key2 = 0;
	e->keytex = 0;
	e->img = (void**)malloc(sizeof(void*) * 101);
	e->data = (char**)malloc(sizeof(char*) * 101);
	e->img[1] = mlx_xpm_file_to_image(e->mlx, "images/im1.xpm", &width, &width);
	e->img[2] = mlx_xpm_file_to_image(e->mlx, "images/im2.xpm", &width, &width);
	e->img[3] = mlx_xpm_file_to_image(e->mlx, "images/im3.xpm", &width, &width);
	e->img[4] = mlx_xpm_file_to_image(e->mlx, "images/im4.xpm", &width, &width);
	e->img[5] = mlx_xpm_file_to_image(e->mlx, "images/im5.xpm", &width, &width);
	e->img[6] = mlx_xpm_file_to_image(e->mlx, "images/im6.xpm", &width, &width);
	e->img[7] = mlx_xpm_file_to_image(e->mlx, "images/im7.xpm", &width, &width);
	e->img[8] = mlx_xpm_file_to_image(e->mlx, "images/sb2.xpm", &width, &width);
	e->img[9] = mlx_xpm_file_to_image(e->mlx, "images/obj1.xpm", &width, &width);
	e->img[10] = mlx_xpm_file_to_image(e->mlx, "images/obj2.xpm", &width, &width);
	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_key_up_hook(e->win, key_up_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_mouse_move_hook(e->win, mouse_move_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
