/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_text_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:58:48 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:26:31 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_text_line(t_pict pict, t_env *e)
{
	t_flo	flo;

	pict.y = pict.drawend;
	if (pict.tex != 5)
	{
		while (pict.y < SIZE_W)
		{
			flo.currentdist =  (double)SIZE_W / (2.0 * (double)pict.y - (double)SIZE_W);
			flo.weight = flo.currentdist / pict.perpwalldist;
			flo.currentfloorx = flo.weight * pict.floorxwall + (1.0 - flo.weight) * (double)e->xcam;
			flo.currentfloory = flo.weight * pict.floorywall + (1.0 - flo.weight) * (double)e->ycam;
			flo.floortexx = (int)(flo.currentfloorx * (double)SIZE_T) % SIZE_T;
			flo.floortexy = (int)(flo.currentfloory * (double)SIZE_T) % SIZE_T;
			if(pict.drawend != SIZE_W - 1 && (int)(flo.currentfloorx) < 32 && (int)(flo.currentfloory) < 32) 
			{
				flo.x = pict.x;
				if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] > 0 && e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] < 9 )
				{
					flo.y = SIZE_W - pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] + 1;
					ft_cop_floor(flo, e);
					flo.y = pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)];
					ft_cop_floor(flo, e);
				}
				else if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] == 0 || e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] == 21 )
				{
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)];
					flo.y = pict.y;
					ft_cop_floor(flo, e);
				}
				else if (e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)] >= 0 )
				{
					flo.y = SIZE_W - pict.y;
					flo.tex = 6;
					ft_cop_floor(flo, e);
					flo.y = pict.y;
					flo.tex = e->map2[(int)(flo.currentfloorx)][(int)(flo.currentfloory)];
					ft_cop_floor(flo, e);
				}
			}
			pict.y++;
		}
	}
	pict.y = pict.drawstart;
	while (pict.y < pict.drawend)
	{	
		if (pict.tex != 5)
			pict.d = pict.y * 256 - SIZE_W * 128 + pict.lineheight * 128;
		else 
			pict.d = (pict.y - pict.drawstart) * 256;
		pict.texy = ((pict.d * SIZE_T) / pict.lineheight) / 256;
		ft_cop_wall(pict, e);
		pict.y++;
	}
}
