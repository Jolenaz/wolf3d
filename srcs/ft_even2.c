/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_even2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:44:38 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/23 15:48:14 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_open_door(t_env *e)
{
	static int i = 0;

	if (i < 20)
	{
		e->dd += 10;
		i++;
	}
	else
	{
		i = 0;
		e->key49 = 0;
		e->dd = 0;
		if (e->qr == 3)
		{
			e->map[15][8] = 0;
			e->map3[15][9] = -3;
		}
		else if (e->qr == 4)
		{
			e->map[7][15] = 0;
			e->map3[7][14] = -4;
		}
		else if (e->qr == 5)
		{
			e->map[1][13] = 0;
			e->map3[1][12] = -5;
		}
	}

}