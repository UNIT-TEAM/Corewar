/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 19:18:46 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/20 18:45:11 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char			**get_data(int const fd, t_fdlist **mstruct)
{
	t_fdlist		*thislist;
	t_fdlist		*prevlist;

	thislist = *mstruct;
	prevlist = NULL;
	while (thislist)
	{
		if (thislist->fd == fd)
			return (&(thislist->buf));
		prevlist = thislist;
		thislist = thislist->next;
	}
	if (!(thislist = (t_fdlist *)malloc(sizeof(t_fdlist))))
		return (NULL);
	thislist->fd = fd;
	thislist->next = NULL;
	thislist->buf = ft_strnew(0);
	if (prevlist == NULL)
		(*mstruct = thislist);
	else
		(prevlist->next = thislist);
	return (&(thislist->buf));
}

static int			create_line(char **buf, char **line, int isread)
{
	size_t			i;
	char			*tmp;

	i = -1;
	while ((*buf)[++i] != '\0')
		if ((*buf)[i] == '\n')
		{
			*line = ft_strsub(*buf, 0, i);
			tmp = *buf;
			*buf = ft_strsub(*buf, (unsigned int)i + 1, (ft_strlen(*buf) - i));
			ft_strdel(&tmp);
			return (1);
		}
	if (isread == 0 && **buf != '\0')
	{
		*line = ft_strsub(*buf, 0, i);
		ft_strclr(*buf);
		return (1);
	}
	return (0);
}

static int			ne_vlezlo(char **kek, char **line, int i, char *buf)
{
	if (create_line(kek, line, i) == 1)
	{
		ft_strdel(&buf);
		return (1);
	}
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	int					i;
	char				*buf;
	char				*tmp;
	char				**kek;
	static t_fdlist		*mstruct;

	if ((int)fd < 0 || !line || BUFF_SIZE <= 0 || \
		!(buf = ft_strnew(BUFF_SIZE)) || read((fd), buf, 0) == -1)
		return (-1);
	kek = get_data(fd, &mstruct);
	while ((i = (int)read((fd), buf, BUFF_SIZE)))
	{
		tmp = *kek;
		*kek = ft_strjoin(*kek, buf);
		ft_strdel(&tmp);
		if (ne_vlezlo(kek, line, i, buf) == 1)
			return (1);
		ft_strclr(buf);
	}
	if (*kek != '\0' && ne_vlezlo(kek, line, i, buf) == 1)
		return (1);
	ft_strdel(&buf);
	return ((i == -1) ? (-1) : 0);
}
