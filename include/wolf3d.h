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

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		**img;
	char		**data;
	int			lmap;
	int			hmap;
	int			**map;
	int			**map2;
	double		zbuff[SIZE_W];
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
	int			key123;
	int			key124;
	int			keytex;
	t_obj		*tabobj;
	int			nbobj;
}				t_env;

void			ft_print_map(t_env *e);
void			ft_print_map2(t_env *e);
void			ft_print_tabobj(t_env *e);
void			ft_creat_env(t_env *e);
void			ft_creat_obj_env(t_env *e);
void			ft_sort_obj(t_env *e);
void			ft_read(int fd);

#endif
