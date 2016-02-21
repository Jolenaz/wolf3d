#include "wolf3d.h"

int		ft_couleur(int wall, int side)
{
	if (wall == 1 || (wall == 12 && side == 0) || (wall == 21 && side == 0) || (wall == 12 && side == 0))
		return (0x000099);
	else if (wall == 2 || (wall == 23 && side == 1) || (wall == 21 && side == 1) || (wall == 12 && side == 1))
		return (0xff0000);
	else if (wall == 3 || (wall == 23 && side == 0))
		return (0xffff00);
	else if (wall == 4)
		return (0x66ff00);
	return (0);
}

void	ft_putline(int x, int drawstart, int drawend, int wall, t_env *e, int side)
{
	int y;
	unsigned int couleur;

	y = 0;
	couleur = 0x666666;
	while (y < SIZE_W)
	{
		if (y < drawstart)
			couleur = 0x77b5fe;
		else if (y < drawend)
			couleur = ft_couleur(wall, side);
		else 
			couleur = 0xcccccc;
		put_pixelle(x, y, &couleur, e);
		y++;
	}
}

