/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_up_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:28:05 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 16:03:48 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_up_hook(int kc, t_env *e)
{
	if (kc == 13 || kc == 126)
		e->key13 = 0;
	if (kc == 1 || kc == 125)
		e->key1 = 0;
	if (kc == 0)
		e->key0 = 0;
	if (kc == 2)
		e->key2 = 0;
	if (kc == 123)
		e->key123 = 0;
	if (kc == 124)
		e->key124 = 0;
	if (kc == 17 && e->keytex)
		e->keytex = 0;
	else if (kc == 17)
		e->keytex = 1;
	return (0);
}
