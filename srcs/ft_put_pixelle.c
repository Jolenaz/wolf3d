#include "wolf3d.h"

void	put_pixelle(int x, int y, unsigned int *couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = couleur;
	c = (unsigned char*)e->data[0] + x * 4 + y * 4 * SIZE_W;
	*c = *((unsigned char*)ptrc);
	*(c + 1) = *((unsigned char*)ptrc + 1);
	*(c + 2) = *((unsigned char*)ptrc + 2);
	*(c + 3) = *((unsigned char*)ptrc + 3);
}

void	put_pixelle_sb(int x, int y, unsigned int *couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = couleur;
	c = (unsigned char*)e->data[1] + x * 4 + y * 4 * SIZE_W;
	*c = *((unsigned char*)ptrc);
	*(c + 1) = *((unsigned char*)ptrc + 1);
	*(c + 2) = *((unsigned char*)ptrc + 2);
	*(c + 3) = *((unsigned char*)ptrc + 3);
}
