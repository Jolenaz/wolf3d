/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:14:21 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 10:51:04 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define SIZE_W 1000
# define SIZE_T 200
# define SIZE_O 200
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_obj
{
	int			x;
	int			y;
	int			type;
	double		dist;
}				t_obj;

typedef struct	s_data
{
	int			bpp;
	int			ls;
	int			endian;
}				t_data;

typedef	struct	s_ray
{
	double		camerax;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	double		wallx;
}				t_ray;

typedef struct	s_flo
{
	double		currentdist;
	double		weight;
	double		currentfx;
	double		currentfy;
	int			floortexx;
	int			floortexy;
	int			x;
	int			y;
	int			tex;
}				t_flo;

typedef struct	s_tmpo
{
	double		xobj;
	double		yobj;
	double		invdev;
	double		transformx;
	double		transformy;
	int			xscreenobj;
	int			drawstarty;
	int			drawendy;
	int			objwidth;
	int			objheight;
	int			drawstartx;
	int			drawendx;
	int			d;
}				t_tmpo;

typedef struct	s_pict
{
	int			texx;
	int			texy;
	int			y;
	int			x;
	int			d;
	int			tex;
	int			side;
	int			drawstart;
	int			drawend;
	int			lineheight;
	double		floorxwall;
	double		floorywall;
	double		perpwalldist;

}				t_pict;

typedef struct	s_zdoor
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	int			side;
}				t_zdoor;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		**img;
	void		**img_wall;
	void		**img_door;
	void		**img_bras;
	void		**img_sb;
	void		**img_floor;
	void		**img_obj;
	char		**data;
	char		**data_wall;
	char		**data_door;
	char		**data_bras;
	char		**data_sb;
	char		**data_floor;
	char		**data_obj;
	int			pause;
	int			lmap;
	int			hmap;
	int			**map;
	int			**map2;
	int			**map3;
	double		zbuff[SIZE_W];
	double		zisdoor[SIZE_W];
	t_zdoor		zdoor[SIZE_W];
	double		xcam;
	double		ycam;
	double		xscreen;
	double		yscreen;
	double		xdir;
	double		ydir;
	int			key13;
	int			key1;
	int			key0;
	int			key2;
	int			key49;
	int			key123;
	int			key53;
	int			key124;
	int			keytex;
	int			help;
	int			take;
	int			show;
	int			qr;
	int			vic;
	t_obj		*tabobj;
	int			nbobj;
	int			dd;
}				t_env;

void			ft_creat_env(t_env *e);
void			ft_creat_obj_env(t_env *e);
void			ft_creat_img(t_env *e);
void			ft_sort_obj(t_env *e);
void			ft_read(int fd);
void			put_pixelle(int x, int y, unsigned int *c, t_env *e);
void			put_pixelle_sb(int x, int y, unsigned int *c, t_env *e);
void			ft_putline(t_pict pict, t_env *e);
void			ft_put_text_line(t_pict pict, t_env *e);
void			ft_put_obj(t_env *e);
void			ft_put_skybox(t_env *e);
void			ft_put_door(t_env *e);
void			ft_put_door2(t_env *e, t_pict *pict);
void			ft_put_door_line(t_pict pict, t_env *e);
void			ft_move_pause(t_env *e);
void			ft_move_back_pause(t_env *e);
void			ft_take_pic(t_env *e);
void			ft_show_pic(t_env *e);
void			ft_check_vic(t_env *e);
void			ft_modim(t_env *e);
void			ft_modim_suite(t_env *e, t_ray *ray, t_pict *pict);
void			ft_cop_door(t_pict pict, t_env *e);
void			ft_cop_wall(t_pict pict, t_env *e);
void			ft_cop_floor(t_flo flo, t_env *e);
int				mouse_hook(int b, int x, int y, t_env *e);
int				mouse_move_hook(int x, int y, t_env *e);
int				key_down_hook(int kc, t_env *e);
int				key_up_hook(int kc, t_env *e);
int				loop_hook(t_env *e);
void			ft_open_door(t_env *e);
void			ft_init_buff(t_env *e);
void			ft_init_wimg(t_env *e);
void			ft_init_fimg(t_env *e);
void			ft_init_dsbimg(t_env *e);
void			ft_init_oimg(t_env *e);
void			ft_init_b1_img(t_env *e);
void			ft_init_b2_img(t_env *e);
void			ft_init_malloc(t_env *e);
void			ft_key_a(t_env *e, double l);
void			ft_key_b(t_env *e, double l);
void			ft_key_c(t_env *e, double l);
void			ft_key_d(t_env *e, double l);

#endif
