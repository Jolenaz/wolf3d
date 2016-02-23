/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_im.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:56:56 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inlcude "wolf3d.h"


void	ft_init_img(t_env *e)
{
	e->img_wall[1] = mlx_xpm_file_to_image(e->mlx, "images/wall1.xpm", &w, &w);
	e->img_wall[2] = mlx_xpm_file_to_image(e->mlx, "images/wall2.xpm", &w, &w);
	e->img_wall[3] = mlx_xpm_file_to_image(e->mlx, "images/wall3.xpm", &w, &w);
	e->img_wall[4] = mlx_xpm_file_to_image(e->mlx, "images/wall4.xpm", &w, &w);
	e->img_wall[5] = mlx_xpm_file_to_image(e->mlx, "images/wall5.xpm", &w, &w);
	e->img_wall[6] = mlx_xpm_file_to_image(e->mlx, "images/wall6.xpm", &w, &w);
	e->img_wall[7] = mlx_xpm_file_to_image(e->mlx, "images/wall7.xpm", &w, &w);
	e->img_wall[8] = mlx_xpm_file_to_image(e->mlx, "images/wall8.xpm", &w, &w);
	e->img_wall[9] = mlx_xpm_file_to_image(e->mlx, "images/wall9.xpm", &w, &w);
	e->img_wall[10] = mlx_xpm_file_to_image(e->mlx, "images/wall10.xpm", &w, &w);
	e->img_wall[11] = mlx_xpm_file_to_image(e->mlx, "images/wall11.xpm", &w, &w);
	e->img_wall[14] = mlx_xpm_file_to_image(e->mlx, "images/wall14.xpm", &w, &w);
	e->img_wall[13] = mlx_xpm_file_to_image(e->mlx, "images/wall13.xpm", &w, &w);
	e->img_wall[15] = mlx_xpm_file_to_image(e->mlx, "images/wall15.xpm", &w, &w);
	e->img_wall[16] = mlx_xpm_file_to_image(e->mlx, "images/wall16.xpm", &w, &w);
	e->img_wall[17] = mlx_xpm_file_to_image(e->mlx, "images/wall17.xpm", &w, &w);
	e->img_wall[18] = mlx_xpm_file_to_image(e->mlx, "images/wall18.xpm", &w, &w);
	e->img_wall[19] = mlx_xpm_file_to_image(e->mlx, "images/wall19.xpm", &w, &w);
	e->img_wall[20] = mlx_xpm_file_to_image(e->mlx, "images/wall20.xpm", &w, &w);
	e->img_wall[22] = mlx_xpm_file_to_image(e->mlx, "images/wall22.xpm", &w, &w);
	e->img_wall[23] = mlx_xpm_file_to_image(e->mlx, "images/wall23.xpm", &w, &w);
	e->img_wall[24] = mlx_xpm_file_to_image(e->mlx, "images/wall24.xpm", &w, &w);
	e->img_door[1] = mlx_xpm_file_to_image(e->mlx, "images/door1.xpm", &w, &w);
	e->img_door[3] = mlx_xpm_file_to_image(e->mlx, "images/door3.xpm", &w, &w);
	e->img_door[4] = mlx_xpm_file_to_image(e->mlx, "images/door4.xpm", &w, &w);
}
