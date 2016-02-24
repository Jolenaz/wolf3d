/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:14:13 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 17:14:14 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_cop_obj(t_pict pict, t_env *e)
{	
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = (unsigned int*)malloc(sizeof(unsigned int));
	c = (unsigned char*)e->data_obj[pict.tex] + pict.texx * 4 + pict.texy * 4 * SIZE_O;
	*((unsigned char*)ptrc) = *c;
	*((unsigned char*)ptrc + 1) = *(c + 1);
	*((unsigned char*)ptrc + 2) = *(c + 2);
	*((unsigned char*)ptrc + 3) = *(c + 3);
	if (*ptrc != 0xff000000)
		put_pixelle(pict.x, pict.y, ptrc, e);
	free(ptrc);
}

void	ft_put_obj(t_env *e)
{
	int i;
	t_pict pict;
	t_tmpo tmpo;

	i = 0;
	while (i < e->nbobj)
	{
		tmpo.xobj = e->tabobj[i].x - e->xcam + 0.5;
		tmpo.yobj = e->tabobj[i].y - e->ycam + 0.5;
		tmpo.invdev = 1.0 / (e->xscreen * e->ydir - e->xdir * e->yscreen);
		tmpo.transformx = tmpo.invdev * (e->ydir * tmpo.xobj - e->xdir * tmpo.yobj);
		tmpo.transformy = tmpo.invdev * (-e->yscreen * tmpo.xobj + e->xscreen * tmpo.yobj);
		tmpo.xscreenobj = (int)((SIZE_W / 2) * (1 + tmpo.transformx / tmpo.transformy));
		tmpo.objheight = abs((int)(SIZE_W / tmpo.transformy));
		tmpo.drawstarty = -tmpo.objheight / 2 + SIZE_W / 2;
		if (tmpo.drawstarty < 0)
			tmpo.drawstarty= 0;
		tmpo.drawendy = tmpo.objheight / 2 + SIZE_W / 2;
		if (tmpo.drawendy > SIZE_W)
			tmpo.drawendy = SIZE_W - 1;
		tmpo.objwidth = abs((int)(SIZE_W / tmpo.transformy));
		tmpo.drawstartx = -tmpo.objwidth / 2 + tmpo.xscreenobj;
		if (tmpo.drawstartx < 0)
			tmpo.drawstartx = 0;
		tmpo.drawendx = tmpo.objwidth / 2 + tmpo.xscreenobj;
		if (tmpo.drawendx > SIZE_W)
			tmpo.drawendx = SIZE_W - 1;
		pict.x = tmpo.drawstartx;
		while (pict.x < tmpo.drawendx)
		{
			pict.y = tmpo.drawstarty;
			pict.texx = (int)(256 * (pict.x - (-tmpo.objwidth / 2 + tmpo.xscreenobj)) * SIZE_O / tmpo.objwidth) / 256;
			if (tmpo.transformy > 0 && pict.x > 0 && pict.x < SIZE_W && tmpo.transformy < e->zbuff[pict.x])
			{
				while (pict.y < tmpo.drawendy)
				{
					tmpo.d = pict.y * 256 - SIZE_W * 128 + tmpo.objheight * 128;
					pict.texy = ((tmpo.d * SIZE_O) / tmpo.objheight) / 256;
					pict.tex = e->tabobj[i].type;
					ft_cop_obj(pict, e);
					pict.y++;
				}
			}
			pict.x++;
		}
		i++;
	}
}

