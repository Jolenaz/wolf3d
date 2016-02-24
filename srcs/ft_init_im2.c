/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_imi2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 11:49:28 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:16:52 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_malloc(t_env *e)
{
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
}

void	ft_init_b1_img(t_env *e)
{
	int w;

	w = 256;
	e->img_bras[0] = mlx_xpm_file_to_image(e->mlx, "images/bras.xpm", &w, &w);
	e->img_bras[1] = mlx_xpm_file_to_image(e->mlx, "images/b_a_1.xpm", &w, &w);
	e->img_bras[2] = mlx_xpm_file_to_image(e->mlx, "images/b_a_2.xpm", &w, &w);
	e->img_bras[3] = mlx_xpm_file_to_image(e->mlx, "images/b_a_3.xpm", &w, &w);
	e->img_bras[4] = mlx_xpm_file_to_image(e->mlx, "images/b_a_4.xpm", &w, &w);
	e->img_bras[5] = mlx_xpm_file_to_image(e->mlx, "images/b_a_5.xpm", &w, &w);
	e->img_bras[6] = mlx_xpm_file_to_image(e->mlx, "images/b_a_6.xpm", &w, &w);
	e->img_bras[7] = mlx_xpm_file_to_image(e->mlx, "images/b_vide.xpm", &w, &w);
	e->img_bras[8] = mlx_xpm_file_to_image(e->mlx, "images/b_menu.xpm", &w, &w);
	e->img_bras[9] = mlx_xpm_file_to_image(e->mlx, "images/b_help.xpm", &w, &w);
	e->img_bras[24] = mlx_xpm_file_to_image(e->mlx, "images/b_end.xpm", &w, &w);
	e->img_bras[33] = mlx_xpm_file_to_image(e->mlx, "images/bras3.xpm", &w, &w);
	e->img_bras[34] = mlx_xpm_file_to_image(e->mlx, "images/bras4.xpm", &w, &w);
	e->img_bras[35] = mlx_xpm_file_to_image(e->mlx, "images/bras5.xpm", &w, &w);
}

void	ft_init_b2_img(t_env *e)
{
	int w;

	w = 256;
	e->img_bras[10] = mlx_xpm_file_to_image(e->mlx, "images/b_b_1.xpm", &w, &w);
	e->img_bras[11] = mlx_xpm_file_to_image(e->mlx, "images/b_b_2.xpm", &w, &w);
	e->img_bras[12] = mlx_xpm_file_to_image(e->mlx, "images/b_b_3.xpm", &w, &w);
	e->img_bras[13] = mlx_xpm_file_to_image(e->mlx, "images/b_b_4.xpm", &w, &w);
	e->img_bras[14] = mlx_xpm_file_to_image(e->mlx, "images/b_b_5.xpm", &w, &w);
	e->img_bras[15] = mlx_xpm_file_to_image(e->mlx, "images/b_b_6.xpm", &w, &w);
	e->img_bras[16] = mlx_xpm_file_to_image(e->mlx, "images/b_b_6.xpm", &w, &w);
	e->img_bras[17] = mlx_xpm_file_to_image(e->mlx, "images/b_c_1.xpm", &w, &w);
	e->img_bras[18] = mlx_xpm_file_to_image(e->mlx, "images/b_c_2.xpm", &w, &w);
	e->img_bras[19] = mlx_xpm_file_to_image(e->mlx, "images/b_c_3.xpm", &w, &w);
	e->img_bras[20] = mlx_xpm_file_to_image(e->mlx, "images/b_c_4.xpm", &w, &w);
	e->img_bras[21] = mlx_xpm_file_to_image(e->mlx, "images/b_c_5.xpm", &w, &w);
	e->img_bras[22] = mlx_xpm_file_to_image(e->mlx, "images/b_c_6.xpm", &w, &w);
	e->img_bras[23] = mlx_xpm_file_to_image(e->mlx, "images/b_c_7.xpm", &w, &w);
}
