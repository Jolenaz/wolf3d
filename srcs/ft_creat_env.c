/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 10:44:56 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:56:38 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <time.h>

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
	int w = 256;

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
	ft_init_img(e);
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
	e->img_door[5] = mlx_xpm_file_to_image(e->mlx, "images/door5.xpm", &w, &w);
	e->img_door[6] = mlx_xpm_file_to_image(e->mlx, "images/door6.xpm", &w, &w);
	e->img_door[7] = mlx_xpm_file_to_image(e->mlx, "images/door7.xpm", &w, &w);
	e->img_door[8] = mlx_xpm_file_to_image(e->mlx, "images/door8.xpm", &w, &w);
	e->img_floor[1] = mlx_xpm_file_to_image(e->mlx, "images/floor1.xpm", &w, &w);
	e->img_floor[2] = mlx_xpm_file_to_image(e->mlx, "images/floor2.xpm", &w, &w);
	e->img_floor[3] = mlx_xpm_file_to_image(e->mlx, "images/floor3.xpm", &w, &w);
	e->img_floor[4] = mlx_xpm_file_to_image(e->mlx, "images/floor4.xpm", &w, &w);
	e->img_floor[5] = mlx_xpm_file_to_image(e->mlx, "images/floor5.xpm", &w, &w);
	e->img_floor[6] = mlx_xpm_file_to_image(e->mlx, "images/floor6.xpm", &w, &w);
	e->img_floor[7] = mlx_xpm_file_to_image(e->mlx, "images/floor7.xpm", &w, &w);
	e->img_floor[8] = mlx_xpm_file_to_image(e->mlx, "images/floor8.xpm", &w, &w);
	e->img_floor[9] = mlx_xpm_file_to_image(e->mlx, "images/floor9.xpm", &w, &w);
	e->img_floor[10] = mlx_xpm_file_to_image(e->mlx, "images/floor10.xpm", &w, &w);
	e->img_floor[11] = mlx_xpm_file_to_image(e->mlx, "images/floor11.xpm", &w, &w);
	e->img_floor[12] = mlx_xpm_file_to_image(e->mlx, "images/floor12.xpm", &w, &w);
	e->img_floor[13] = mlx_xpm_file_to_image(e->mlx, "images/floor13.xpm", &w, &w);
	e->img_floor[14] = mlx_xpm_file_to_image(e->mlx, "images/floor14.xpm", &w, &w);
	e->img_floor[15] = mlx_xpm_file_to_image(e->mlx, "images/floor15.xpm", &w, &w);
	e->img_floor[16] = mlx_xpm_file_to_image(e->mlx, "images/floor16.xpm", &w, &w);
	e->img_floor[17] = mlx_xpm_file_to_image(e->mlx, "images/floor17.xpm", &w, &w);
	e->img_floor[18] = mlx_xpm_file_to_image(e->mlx, "images/floor18.xpm", &w, &w);
	e->img_floor[19] = mlx_xpm_file_to_image(e->mlx, "images/floor19.xpm", &w, &w);
	e->img_floor[20] = mlx_xpm_file_to_image(e->mlx, "images/floor20.xpm", &w, &w);
	e->img_floor[0] = mlx_xpm_file_to_image(e->mlx, "images/floor0.xpm", &w, &w);
	e->img_sb[2] = mlx_xpm_file_to_image(e->mlx, "images/sb2.xpm", &w, &w);
	e->img_sb[3] = mlx_xpm_file_to_image(e->mlx, "images/sb3.xpm", &w, &w);
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
	e->img_bras[0] = mlx_xpm_file_to_image(e->mlx, "images/bras.xpm", &w, &w);
	e->img_bras[1] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_1.xpm", &w, &w);
	e->img_bras[2] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_2.xpm", &w, &w);
	e->img_bras[3] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_3.xpm", &w, &w);
	e->img_bras[4] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_4.xpm", &w, &w);
	e->img_bras[5] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_5.xpm", &w, &w);
	e->img_bras[6] = mlx_xpm_file_to_image(e->mlx, "images/bras_a_6.xpm", &w, &w);
	e->img_bras[7] = mlx_xpm_file_to_image(e->mlx, "images/menu_vide.xpm", &w, &w);
	e->img_bras[8] = mlx_xpm_file_to_image(e->mlx, "images/menu_menu.xpm", &w, &w);
	e->img_bras[9] = mlx_xpm_file_to_image(e->mlx, "images/menu_help.xpm", &w, &w);
	e->img_bras[10] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_1.xpm", &w, &w);
	e->img_bras[11] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_2.xpm", &w, &w);
	e->img_bras[12] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_3.xpm", &w, &w);
	e->img_bras[13] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_4.xpm", &w, &w);
	e->img_bras[14] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_5.xpm", &w, &w);
	e->img_bras[15] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_6.xpm", &w, &w);
	e->img_bras[16] = mlx_xpm_file_to_image(e->mlx, "images/bras_b_6.xpm", &w, &w);
	e->img_bras[17] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_1.xpm", &w, &w);
	e->img_bras[18] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_2.xpm", &w, &w);
	e->img_bras[19] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_3.xpm", &w, &w);
	e->img_bras[20] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_4.xpm", &w, &w);
	e->img_bras[21] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_5.xpm", &w, &w);
	e->img_bras[22] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_6.xpm", &w, &w);
	e->img_bras[23] = mlx_xpm_file_to_image(e->mlx, "images/bras_c_7.xpm", &w, &w);
	e->img_bras[33] = mlx_xpm_file_to_image(e->mlx, "images/bras3.xpm", &w, &w);
	e->img_bras[34] = mlx_xpm_file_to_image(e->mlx, "images/bras4.xpm", &w, &w);
	e->img_bras[35] = mlx_xpm_file_to_image(e->mlx, "images/bras5.xpm", &w, &w);
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
