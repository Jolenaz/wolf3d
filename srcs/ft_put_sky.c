
#include "wolf3d.h"

void	ft_cop_sb(t_pict pict, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_sb[pict.tex] + pict.texx * 4 + pict.y * 4 * 3000;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle_sb(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_put_skybox(t_env *e)
{
	t_pict pict;

	if (e->map2[(int)e->xcam][(int)e->ycam] <= 2 || e->map2[(int)e->xcam][(int)e->ycam] == 21 )
		pict.tex = 2;
	else 
		pict.tex = 3;
	pict.x = 0;
	while (pict.x < SIZE_W)
	{
		pict.texx = pict.x + (int)(atan2(e->xdir, e->ydir) / M_PI * 1500) + 3000;
		pict.y = 0;
		while (pict.y < SIZE_W)
		{
			ft_cop_sb(pict, e);
			(pict.y)++;
		}
		(pict.x)++;
	}
}
