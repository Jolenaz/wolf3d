#ifndef WOLF3D_H
# define WOLF3D_H
# define SIZE_W 1000

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;
}				t_env;

void			ft_read_map(int fd);
void			ft_creat_env(double **map);

#endif
