/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:51:39 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 15:29:43 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_cop_door(t_pict pict, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (pict.tex == 1 || pict.tex == 2)
		c = (unsigned char*)e->data_door[1] + (pict.texx + e->dd) * 4
			+ pict.texy * 8 * SIZE_T;
	else
		c = (unsigned char*)e->data_door[pict.tex] + (pict.texx + e->dd) * 4
			+ pict.texy * 8 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (*ptrc != 0xff000000)
		put_pixelle(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_cop_wall(t_pict pict, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	if (pict.tex == 1 || (pict.tex == 12 && pict.side == 0) ||
			(pict.tex == 21 && pict.side == 0) ||
			(pict.tex == 12 && pict.side == 0))
		c = (unsigned char*)e->data_wall[1] + pict.texx * 4 +
			pict.texy * 4 * SIZE_T;
	else if (pict.tex == 2 || (pict.tex == 21 && pict.side == 1) ||
			(pict.tex == 12 && pict.side == 1))
		c = (unsigned char*)e->data_wall[2] + pict.texx * 4 +
			pict.texy * 4 * SIZE_T;
	else
		c = (unsigned char*)e->data_wall[pict.tex] + pict.texx * 4 +
			pict.texy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (pict.side == 0 && (pict.tex == 2 || pict.tex == 3))
		*ptrc -= 0x101010;
	put_pixelle(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_cop_floor(t_flo flo, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_floor[flo.tex] + flo.floortexx * 4 +
		flo.floortexy * 4 * SIZE_T;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	put_pixelle(flo.x, flo.y, ptrc, e);
	free(ptrc);
}
