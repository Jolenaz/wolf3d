/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 09:04:38 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/24 14:52:10 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (0);
	if (ft_strcmp(av[1], "maps/map1") != 0)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	ft_read(fd);
	return (0);
}
