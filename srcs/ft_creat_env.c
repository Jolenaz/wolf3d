/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/15 17:58:35 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <time.h>

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

void	ft_cop_door(int texx, int texy, int x, int y, int door, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	door = 0;
	c = (unsigned char*)e->data_door[1] + (texx + e->dd) * 4 + texy * 8 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (*ptrc != 0xff000000)
		put_pixelle(x, y, ptrc, e);
	free(ptrc);
}

void	ft_cop_wall(int texx, int texy, int x, int y, int wall, t_env *e, int side)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (wall == 1 || (wall == 12 && side == 0) || (wall == 21 && side == 0) || (wall == 12 && side == 0))
		c = (unsigned char*)e->data_wall[1] + texx * 4 + texy * 4 * SIZE_T;
	else if (wall == 2 || (wall == 23 && side == 1) || (wall == 21 && side == 1) || (wall == 12 && side == 1))
		c = (unsigned char*)e->data_wall[2] + texx * 4 + texy * 4 * SIZE_T;
	else if (wall == 3 || (wall == 23 && side == 0))
		c = (unsigned char*)e->data_wall[3] + texx * 4 + texy * 4 * SIZE_T;
	else if (wall == 4)
		c = (unsigned char*)e->data_wall[4] + texx * 4 + texy * 4 * SIZE_T;
	else if (wall == 5)
		c = (unsigned char*)e->data_wall[5] + texx * 4 + texy * 4 * SIZE_T;
	else
		c = (unsigned char*)e->data_wall[4] + texx * 4 + texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(x, y, ptrc, e);
	free(ptrc);
}

void	ft_cop_floor(int texx, int texy, int x, int y, int floor, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_floor[floor] + texx * 4 + texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(x, y, ptrc, e);
	free(ptrc);
}

void	ft_cop_sb(int texx, int texy, int x, int y, int wall, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_sb[wall - 6] + texx * 4 + texy * 4 * 3000;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(x, y, ptrc, e);
	free(ptrc);
}
void	ft_cop_obj(int texx, int texy, int x, int y, int obj, t_env *e)
{	
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_obj[obj] + texx * 4 + texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (*ptrc != 0xff000000)
		put_pixelle(x, y, ptrc, e);
	free(ptrc);

}

void	ft_put_text_line(int x, int texx, int drawstart, int drawend, int wall, t_env *e, int side, int lineheight, double distwall, double floorxwall, double floorywall)
{
	int y;
	int d;
	double currentdist;

	y = drawend;
	if (wall != 5)
	{
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
			if(drawend != SIZE_W - 1) 
			{
				if (e->map2[(int)currentfloorx][(int)currentfloory] > 0)
				{
					ft_cop_floor(floortexx, floortexy, x, SIZE_W - y, e->map2[(int)currentfloorx][(int)currentfloory], e);
					ft_cop_floor(floortexx, floortexy, x, y, e->map2[(int)currentfloorx][(int)currentfloory] + 1, e);
				}
				else 
					ft_cop_floor(floortexx, floortexy, x, y, 0, e);
			}
			y++;
		}
	}
	y = drawstart;
	while (y < drawend)
	{	
		if (wall != 5)
			d = y * 256 - SIZE_W * 128 + lineheight * 128;
		else 
			d = (y - drawstart) * 256;
		int texy = ((d * SIZE_T) / lineheight) / 256;
		ft_cop_wall(texx, texy, x, y, wall, e, side);
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

void	ft_put_door_line(int x, int texx, int drawstart, int drawend, int door, t_env *e, int lineheight)
{
	int y;

	y = drawstart;
	while (y < drawend)
	{
		int d = y * 256 - SIZE_W * 128 + lineheight * 128;
		int texy = ((d * SIZE_T) / lineheight) / 256;
		ft_cop_door(texx, texy, x, y, door, e);
		y++;
	}
}

void	ft_put_door(t_env *e)
{
	int x;
	double perpwalldist;

	x = 0;
	while (x < SIZE_W)
	{
		if (e->zisdoor[x])
		{
			if (e->zdoor[x].side == 0)
				perpwalldist = fabs((e->zdoor[x].mapx - e->zdoor[x].rayposx + (1 - e->zdoor[x].stepx) / 2) / e->zdoor[x].raydirx);
			else
				perpwalldist = fabs((e->zdoor[x].mapy - e->zdoor[x].rayposy + (1 - e->zdoor[x].stepy) / 2) / e->zdoor[x].raydiry);
			e->zbuff[x] = perpwalldist;
			int lineheight = (int)(SIZE_W / perpwalldist);
			int drawstart = -lineheight / 2 + SIZE_W / 2;
			if (drawstart < 0)
				drawstart = 0;
			int drawend = lineheight / 2 + SIZE_W / 2;
			if (drawend > SIZE_W)
				drawend = SIZE_W - 1;
			double wallx;
			if (e->zdoor[x].side == 1)
				wallx = e->zdoor[x].rayposx + ((e->zdoor[x].mapy - e->zdoor[x].rayposy + (1 - e->zdoor[x].stepy) / 2) / e->zdoor[x].raydiry) * e->zdoor[x].raydirx;
			else
				wallx = e->zdoor[x].rayposy + ((e->zdoor[x].mapx - e->zdoor[x].rayposx + (1 - e->zdoor[x].stepx) / 2) / e->zdoor[x].raydirx) * e->zdoor[x].raydiry;
			wallx -= floor(wallx);
			int texx = (int)(wallx * (double)SIZE_T);
			if (e->zdoor[x].side == 0 && e->zdoor[x].raydirx > 0)
				texx = SIZE_T - texx - 1;
			if (e->zdoor[x].side == 1 && e->zdoor[x].raydiry < 0)
				texx = SIZE_T - texx - 1;
			if (e->keytex == 1)
			{
				if (e->map2[(int)e->xcam][(int)e->ycam] == 0 && e->map[e->zdoor[x].mapx][e->zdoor[x].mapy] != -2)
					ft_put_door_line(x, texx, drawstart, drawend, abs(e->map[e->zdoor[x].mapx][e->zdoor[x].mapy]), e, lineheight);
				else if (e->map2[(int)e->xcam][(int)e->ycam] == 1 && e->map[e->zdoor[x].mapx][e->zdoor[x].mapy] != -1)
					ft_put_door_line(x, texx, drawstart, drawend, abs(e->map[e->zdoor[x].mapx][e->zdoor[x].mapy]), e, lineheight);
			}
			if (e->map[e->zdoor[x].mapx][e->zdoor[x].mapy] == -1 && e->xdir < 0.5)
				ft_put_text_line(x, texx, 2 * drawstart - drawend, drawstart, 5, e, 0, lineheight, 0, 0, 0);
		}
		x++;
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
			else if (e->map[mapx][mapy] <= -1)
			{
				e->zisdoor[x] = 1;
				e->zdoor[x].mapx = mapx;
				e->zdoor[x].mapy = mapy;
				e->zdoor[x].stepx = stepx;
				e->zdoor[x].stepy = stepy;
				e->zdoor[x].rayposx = rayposx;
				e->zdoor[x].rayposy = rayposy;
				e->zdoor[x].raydirx = raydirx;
				e->zdoor[x].raydiry = raydiry;
				e->zdoor[x].side = side;
			}
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
		if (e->map[mapx][mapy] == 1 || (side == 0 && (e->map[mapx][mapy] == 21 || e->map[mapx][mapy] == 12)))
			ft_put_text_line(x, texx, 2 * drawstart - drawend, drawstart, 5, e, side, lineheight, perpwalldist, floorxwall, floorywall);
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
			ft_cop_sb(texx, y, x, y, 8, e);
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
		double xobj = e->tabobj[i].x - e->xcam + 0.5;
		double yobj = e->tabobj[i].y - e->ycam + 0.5;
		double invdev = 1.0 / (e->xscreen * e->ydir - e->xdir * e->yscreen);
		double transformx = invdev * (e->ydir * xobj - e->xdir * yobj);
		double transformy = invdev * (-e->yscreen * xobj + e->xscreen * yobj);
		int xscreenobj = (int)((SIZE_W / 2) * (1 + transformx / transformy));
		int objheight = abs((int)(SIZE_W / transformy));
		int drawstarty = -objheight / 2 + SIZE_W / 2;
		if (drawstarty < 0)
			drawstarty= 0;
		int drawendy = objheight / 2 + SIZE_W / 2;
		if (drawendy > SIZE_W)
			drawendy = SIZE_W - 1;
		int objwidth = abs((int)(SIZE_W / transformy));
		int drawstartx = -objwidth / 2 + xscreenobj;
		if (drawstartx < 0)
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
					ft_cop_obj(texx, texy, x, y, e->tabobj[i].type, e);
					y++;
				}
			}
			x++;
		}
		i++;
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

void	ft_move_pause(t_env *e)
{
	static int i = 1;

	if (i < 9)
	{
		if (i < 7)
		{
			mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[i], 250, 650);
		}
		else if (i < 9)
		{
			mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[i], 0, 0);
		}
		i++;
		if (i == 9)
		{
			i = 1;
			e->pause = 1;
		}	
	}
}

void	ft_move_back_pause(t_env *e)
{
	static int j = 6;

	if (j > 0)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
		mlx_put_image_to_window(e->mlx, e->win, e->img_bras[j], 250, 650);
		j--;
		if (j == 0)
		{
			j = 6;
			e->pause = 0;
		}	
	}
}

void	ft_take_pic(t_env *e)
{
	static int j = 17;

	if (j < 30)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
		if (j <= 22)
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[j], 250, 650);
		else if (j == 23)
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[23], 0, 0);
		else
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[46 - j], 250, 650);
		j++;
		if (j == 30)
		{
			j = 17;
			e->take = 0;
		}	
	}
}

void	ft_show_pic(t_env *e)
{
	static int j = 10;

	if (j < 23)
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img[0], 0, 0);
		if (j <= 16)
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[j], 250, 650);
		else
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[32 - j], 250, 650);
		j++;
		if (j == 23)
		{
			j = 10;
			e->show = 0;
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
	e->data[0] = mlx_get_data_addr(e->img[0], &bpp, &ls, &endian);
	mlx_clear_window(e->mlx, e->win);
	ft_init_ob_im(e);
	ft_init_buff(e);
	ft_sort_obj(e);
	ft_put_skybox(e);
	ft_modim(e);
	ft_put_obj(e);
	ft_put_door(e);
	ft_put_obj(e);
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

	mlx_destroy_image(e->mlx, e->img[0]);
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
		//	if (kc == 49)
		//		e->key49 = 1;
	}
	if (kc == 53 && e->pause == 0)
		e->key53 = 1;
	if (kc == 53 && e->pause == 1)
		e->key53 = 0;
	if (e->pause == 0)
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
	if (b == 2 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
		e->show = 1;
	if (b == 1 && x && x < SIZE_W && y && y < SIZE_W && e->pause == 0)
		e->take = 1;
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
	e->xcam = 23;
	e->ycam = 13;
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
	e->img_door[1] = mlx_xpm_file_to_image(e->mlx, "images/door1.xpm", &width, &width);
	e->img_floor[1] = mlx_xpm_file_to_image(e->mlx, "images/floor1.xpm", &width, &width);
	e->img_floor[2] = mlx_xpm_file_to_image(e->mlx, "images/floor2.xpm", &width, &width);
	e->img_floor[0] = mlx_xpm_file_to_image(e->mlx, "images/floor0.xpm", &width, &width);
	e->img_sb[2] = mlx_xpm_file_to_image(e->mlx, "images/sb2.xpm", &width, &width);
	e->img_obj[1] = mlx_xpm_file_to_image(e->mlx, "images/obj1.xpm", &width, &width);
	e->img_obj[2] = mlx_xpm_file_to_image(e->mlx, "images/obj2.xpm", &width, &width);
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
	e->data_wall[1] = mlx_get_data_addr(e->img_wall[1], &bpp, &ls, &endian);
	e->data_wall[2] = mlx_get_data_addr(e->img_wall[2], &bpp, &ls, &endian);
	e->data_wall[3] = mlx_get_data_addr(e->img_wall[3], &bpp, &ls, &endian);
	e->data_wall[4] = mlx_get_data_addr(e->img_wall[4], &bpp, &ls, &endian);
	e->data_wall[5] = mlx_get_data_addr(e->img_wall[5], &bpp, &ls, &endian);
	e->data_door[1] = mlx_get_data_addr(e->img_door[1], &bpp, &ls, &endian);
	e->data_sb[2] = mlx_get_data_addr(e->img_sb[2], &bpp, &ls, &endian);
	e->data_floor[1] = mlx_get_data_addr(e->img_floor[1], &bpp, &ls, &endian);
	e->data_floor[2] = mlx_get_data_addr(e->img_floor[2], &bpp, &ls, &endian);
	e->data_floor[0] = mlx_get_data_addr(e->img_floor[0], &bpp, &ls, &endian);
	e->data_obj[1] = mlx_get_data_addr(e->img_obj[1], &bpp, &ls, &endian);
	e->data_obj[2] = mlx_get_data_addr(e->img_obj[2], &bpp, &ls, &endian);
	mlx_key_down_hook(e->win, key_down_hook, e);
	mlx_key_up_hook(e->win, key_up_hook, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_mouse_move_hook(e->win, mouse_move_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
