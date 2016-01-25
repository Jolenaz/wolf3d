/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/23 16:18:26 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#define BUFF_SIZE 1024

static int	ft_cop(char **str1, char **line, char **str2)
{
	char **vid;

	vid = (char**)malloc(sizeof(char*));
	*vid = NULL;
	*(ft_strchr(*str1, '\n')) = '\0';
	if ((*vid = ft_strjoin(*line, *str1)) == NULL)
		return (-1);
	ft_strdel(line);
	*line = *vid;
	if (str2 != str1)
		free(*str2);
	if ((*str2 = ft_strdup(ft_strchr(*str1, '\0') + 1)) == NULL)
		return (-1);
	return (1);
}

static int	norme(const int fd, char **line, char **rest, int *tete)
{
	char		**vid;
	char		*buff;

	if ((buff = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	vid = (char**)malloc(sizeof(char*));
	*vid = NULL;
	while ((*tete = read(fd, buff, BUFF_SIZE)) && *tete != -1)
	{
		if (*tete <= BUFF_SIZE)
			buff[*tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(&buff, line, rest));
		else
		{
			if ((*vid = ft_strjoin(*line, buff)) == NULL)
				return (-1);
			ft_strdel(line);
			*line = *vid;
		}
	}
	ft_strdel(&buff);
	return (*tete);
}

static int	read_get_next_line(const int fd, char **line, char **rest)
{
	int			tete;

	if (*rest == NULL)
		*rest = ft_strnew(BUFF_SIZE);
	else if (ft_strchr(*rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	else if ((*line = ft_strjoin(*line, *rest)) == NULL)
		return (-1);
	if (norme(fd, line, rest, &tete) == 1)
		return (1);
	return (tete);
}

static void	init_doc(int fd, int *filed, t_doc **next, char **rest)
{
	*filed = fd;
	*next = NULL;
	*rest = NULL;
}

int			get_next_line(const int fd, char **line)
{
	static t_doc	doc;
	t_doc			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((*line = ft_strnew(1)) == NULL)
		return (-1);
	tmp = &doc;
	if (tmp->rest == NULL)
	{
		init_doc(fd, &(doc.filed), &(doc.next), &(doc.rest));
		return (read_get_next_line(fd, line, &(doc.rest)));
	}
	while (tmp->filed != fd && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->filed != fd)
	{
		if ((tmp->next = (t_doc*)malloc(sizeof(t_doc))) == NULL)
			return (-1);
		init_doc(fd, &(tmp->next->filed),
				&(tmp->next->next), &(tmp->next->rest));
		return (read_get_next_line(fd, line, &tmp->next->rest));
	}
	return (read_get_next_line(fd, line, &tmp->rest));
}
