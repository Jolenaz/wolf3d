/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_even1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:31:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 15:33:30 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[46 -
					j], 250, 650);
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
			mlx_put_image_to_window(e->mlx, e->win, e->img_bras[32 -
					j], 250, 650);
		j++;
		if (j == 23)
		{
			j = 10;
			e->show = 0;
		}
	}
}

void	ft_check_vic(t_env *e)
{
	if ((int)e->xcam == 2 && (int)e->ycam == 16)
		e->map3[3][16] = 0;
	else
		e->map3[3][16] = 1;
	if ((int)e->xcam == 3 && (int)e->ycam == 16)
	{
		e->vic = 1;
		e->pause = 1;
		e->key53 = 1;
	}
}
