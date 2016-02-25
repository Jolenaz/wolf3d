/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_text_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 14:58:48 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 10:52:40 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_ptl3(t_flo *flo, t_pict *pict, t_env *e)
{
	flo->y = SIZE_W - pict->y;
	flo->tex = e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)]
		+ 1;
	ft_cop_floor(*flo, e);
	flo->y = pict->y;
	flo->tex = e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)];
	ft_cop_floor(*flo, e);
}

static void	ft_ptl2(t_flo *flo, t_pict *pict, t_env *e)
{
	if (e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)] > 0 &&
			e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)] < 9)
		ft_ptl3(flo, pict, e);
	else if (e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)] == 0
			|| e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)] == 21)
	{
		flo->tex = e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)];
		flo->y = pict->y;
		ft_cop_floor(*flo, e);
	}
	else if (e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)] >= 0)
	{
		flo->y = SIZE_W - pict->y;
		flo->tex = 6;
		ft_cop_floor(*flo, e);
		flo->y = pict->y;
		flo->tex = e->map2[(int)(flo->currentfx)][(int)(flo->currentfy)];
		ft_cop_floor(*flo, e);
	}
}

static void	ft_ptl(t_pict *pict, t_env *e)
{
	t_flo	flo;

	flo.currentdist = (double)SIZE_W / (2.0 * (double)pict->y - (double)SIZE_W);
	flo.weight = flo.currentdist / pict->perpwalldist;
	flo.currentfx = flo.weight * pict->floorxwall + (1.0 - flo.weight)
		* (double)e->xcam;
	flo.currentfy = flo.weight * pict->floorywall + (1.0 - flo.weight)
		* (double)e->ycam;
	flo.floortexx = (int)(flo.currentfx * (double)SIZE_T) % SIZE_T;
	flo.floortexy = (int)(flo.currentfy * (double)SIZE_T) % SIZE_T;
	if (pict->drawend != SIZE_W - 1 && (int)(flo.currentfx) < 32 &&
			(int)(flo.currentfy) < 32)
	{
		flo.x = pict->x;
		ft_ptl2(&flo, pict, e);
	}
}

void		ft_put_text_line(t_pict pict, t_env *e)
{
	pict.y = pict.drawend;
	if (pict.tex != 5)
	{
		while (pict.y < SIZE_W)
		{
			ft_ptl(&pict, e);
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
