/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:11:13 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 17:11:14 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_couleur(int wall, int side)
{
	if (wall == 1 || (wall == 12 && side == 0) ||
			(wall == 21 && side == 0) ||
			(wall == 12 && side == 0))
		return (0x000099);
	else if (wall == 2 || (wall == 23 && side == 1) ||
			(wall == 21 && side == 1) ||
			(wall == 12 && side == 1))
		return (0xff0000);
	else if (wall == 3 || (wall == 23 && side == 0))
		return (0xffff00);
	else if (wall == 4)
		return (0x66ff00);
	return (0);
}

void	ft_putline(t_pict pict, t_env *e)
{
	unsigned int couleur;

	pict.y = 0;
	couleur = 0x666666;
	while (pict.y < SIZE_W)
	{
		if (pict.y < pict.drawstart)
			couleur = 0x77b5fe;
		else if (pict.y < pict.drawend)
			couleur = ft_couleur(pict.tex, pict.side);
		else
			couleur = 0xcccccc;
		put_pixelle(pict.x, pict.y, &couleur, e);
		pict.y++;
	}
}
