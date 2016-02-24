/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_im.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:42:53 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_wimg(t_env *e)
{
	int	w;

	w = 256;
	e->img_wall[1] = mlx_xpm_file_to_image(e->mlx, "images/w1.xpm", &w, &w);
	e->img_wall[2] = mlx_xpm_file_to_image(e->mlx, "images/w2.xpm", &w, &w);
	e->img_wall[3] = mlx_xpm_file_to_image(e->mlx, "images/w3.xpm", &w, &w);
	e->img_wall[4] = mlx_xpm_file_to_image(e->mlx, "images/w4.xpm", &w, &w);
	e->img_wall[5] = mlx_xpm_file_to_image(e->mlx, "images/w5.xpm", &w, &w);
	e->img_wall[6] = mlx_xpm_file_to_image(e->mlx, "images/w6.xpm", &w, &w);
	e->img_wall[7] = mlx_xpm_file_to_image(e->mlx, "images/w7.xpm", &w, &w);
	e->img_wall[8] = mlx_xpm_file_to_image(e->mlx, "images/w8.xpm", &w, &w);
	e->img_wall[9] = mlx_xpm_file_to_image(e->mlx, "images/w9.xpm", &w, &w);
	e->img_wall[10] = mlx_xpm_file_to_image(e->mlx, "images/w10.xpm", &w, &w);
	e->img_wall[11] = mlx_xpm_file_to_image(e->mlx, "images/w11.xpm", &w, &w);
	e->img_wall[14] = mlx_xpm_file_to_image(e->mlx, "images/w14.xpm", &w, &w);
	e->img_wall[13] = mlx_xpm_file_to_image(e->mlx, "images/w13.xpm", &w, &w);
	e->img_wall[15] = mlx_xpm_file_to_image(e->mlx, "images/w15.xpm", &w, &w);
	e->img_wall[16] = mlx_xpm_file_to_image(e->mlx, "images/w16.xpm", &w, &w);
	e->img_wall[17] = mlx_xpm_file_to_image(e->mlx, "images/w17.xpm", &w, &w);
	e->img_wall[18] = mlx_xpm_file_to_image(e->mlx, "images/w18.xpm", &w, &w);
	e->img_wall[19] = mlx_xpm_file_to_image(e->mlx, "images/w19.xpm", &w, &w);
	e->img_wall[20] = mlx_xpm_file_to_image(e->mlx, "images/w20.xpm", &w, &w);
	e->img_wall[22] = mlx_xpm_file_to_image(e->mlx, "images/w22.xpm", &w, &w);
	e->img_wall[23] = mlx_xpm_file_to_image(e->mlx, "images/w23.xpm", &w, &w);
	e->img_wall[24] = mlx_xpm_file_to_image(e->mlx, "images/w24.xpm", &w, &w);
}

void	ft_init_fimg(t_env *e)
{
	int	w;

	w = 256;
	e->img_floor[1] = mlx_xpm_file_to_image(e->mlx, "images/f1.xpm", &w, &w);
	e->img_floor[2] = mlx_xpm_file_to_image(e->mlx, "images/f2.xpm", &w, &w);
	e->img_floor[3] = mlx_xpm_file_to_image(e->mlx, "images/f3.xpm", &w, &w);
	e->img_floor[4] = mlx_xpm_file_to_image(e->mlx, "images/f4.xpm", &w, &w);
	e->img_floor[5] = mlx_xpm_file_to_image(e->mlx, "images/f5.xpm", &w, &w);
	e->img_floor[6] = mlx_xpm_file_to_image(e->mlx, "images/f6.xpm", &w, &w);
	e->img_floor[7] = mlx_xpm_file_to_image(e->mlx, "images/f7.xpm", &w, &w);
	e->img_floor[8] = mlx_xpm_file_to_image(e->mlx, "images/f8.xpm", &w, &w);
	e->img_floor[9] = mlx_xpm_file_to_image(e->mlx, "images/f9.xpm", &w, &w);
	e->img_floor[10] = mlx_xpm_file_to_image(e->mlx, "images/f10.xpm", &w, &w);
	e->img_floor[11] = mlx_xpm_file_to_image(e->mlx, "images/f11.xpm", &w, &w);
	e->img_floor[12] = mlx_xpm_file_to_image(e->mlx, "images/f12.xpm", &w, &w);
	e->img_floor[13] = mlx_xpm_file_to_image(e->mlx, "images/f13.xpm", &w, &w);
	e->img_floor[14] = mlx_xpm_file_to_image(e->mlx, "images/f14.xpm", &w, &w);
	e->img_floor[15] = mlx_xpm_file_to_image(e->mlx, "images/f15.xpm", &w, &w);
	e->img_floor[16] = mlx_xpm_file_to_image(e->mlx, "images/f16.xpm", &w, &w);
	e->img_floor[17] = mlx_xpm_file_to_image(e->mlx, "images/f17.xpm", &w, &w);
	e->img_floor[18] = mlx_xpm_file_to_image(e->mlx, "images/f18.xpm", &w, &w);
	e->img_floor[19] = mlx_xpm_file_to_image(e->mlx, "images/f19.xpm", &w, &w);
	e->img_floor[20] = mlx_xpm_file_to_image(e->mlx, "images/f20.xpm", &w, &w);
	e->img_floor[21] = mlx_xpm_file_to_image(e->mlx, "images/f21.xpm", &w, &w);
	e->img_floor[0] = mlx_xpm_file_to_image(e->mlx, "images/f0.xpm", &w, &w);
}

void	ft_init_dsbimg(t_env *e)
{
	int	w;

	w = 256;
	e->img_wall[25] = mlx_xpm_file_to_image(e->mlx, "images/w25.xpm", &w, &w);
	e->img_door[1] = mlx_xpm_file_to_image(e->mlx, "images/door1.xpm", &w, &w);
	e->img_door[3] = mlx_xpm_file_to_image(e->mlx, "images/door3.xpm", &w, &w);
	e->img_door[4] = mlx_xpm_file_to_image(e->mlx, "images/door4.xpm", &w, &w);
	e->img_door[5] = mlx_xpm_file_to_image(e->mlx, "images/door5.xpm", &w, &w);
	e->img_door[6] = mlx_xpm_file_to_image(e->mlx, "images/door6.xpm", &w, &w);
	e->img_door[7] = mlx_xpm_file_to_image(e->mlx, "images/door7.xpm", &w, &w);
	e->img_door[8] = mlx_xpm_file_to_image(e->mlx, "images/door8.xpm", &w, &w);
	e->img_sb[2] = mlx_xpm_file_to_image(e->mlx, "images/sb2.xpm", &w, &w);
	e->img_sb[3] = mlx_xpm_file_to_image(e->mlx, "images/sb3.xpm", &w, &w);
}

void	ft_init_oimg(t_env *e)
{
	int w;

	w = 256;
	e->img_obj[1] = mlx_xpm_file_to_image(e->mlx, "images/obj1.xpm", &w, &w);
	e->img_obj[2] = mlx_xpm_file_to_image(e->mlx, "images/obj2.xpm", &w, &w);
	e->img_obj[3] = mlx_xpm_file_to_image(e->mlx, "images/obj3.xpm", &w, &w);
	e->img_obj[4] = mlx_xpm_file_to_image(e->mlx, "images/obj4.xpm", &w, &w);
	e->img_obj[5] = mlx_xpm_file_to_image(e->mlx, "images/obj5.xpm", &w, &w);
	e->img_obj[6] = mlx_xpm_file_to_image(e->mlx, "images/obj6.xpm", &w, &w);
	e->img_obj[7] = mlx_xpm_file_to_image(e->mlx, "images/obj7.xpm", &w, &w);
	e->img_obj[8] = mlx_xpm_file_to_image(e->mlx, "images/obj8.xpm", &w, &w);
	e->img_obj[9] = mlx_xpm_file_to_image(e->mlx, "images/obj9.xpm", &w, &w);
	e->img_obj[10] = mlx_xpm_file_to_image(e->mlx, "images/obj10.xpm", &w, &w);
	e->img_obj[11] = mlx_xpm_file_to_image(e->mlx, "images/obj11.xpm", &w, &w);
	e->img_obj[12] = mlx_xpm_file_to_image(e->mlx, "images/obj12.xpm", &w, &w);
	e->img_obj[13] = mlx_xpm_file_to_image(e->mlx, "images/obj13.xpm", &w, &w);
}
