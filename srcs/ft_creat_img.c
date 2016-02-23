/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:40:38 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:42:53 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
}
