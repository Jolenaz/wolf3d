#ifndef WOLF3D_H
# define WOLF3D_H
# define SIZE_W 1000

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img2;
	char		*data;
	int			**map;
	int			lmap;
	int			hmap;
	double		xcam;
	double		ycam;
	double		xscreen;
	double		yscreen;
	double		xdir;
	double		ydir;
}				t_env;

void			ft_print_map(t_env *e);
void			ft_creat_env(t_env *e);
void			ft_read(int fd);

#endif
