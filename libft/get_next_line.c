/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:13:27 by tgogol            #+#    #+#             */
/*   Updated: 2017/01/26 09:17:46 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**create_and_find_list(t_gnl **h, int fd)
{
	t_gnl *tmp;

	tmp = *h;
	while (tmp)
	{
		if (tmp->fdc == fd)
			return (&(tmp->s));
		tmp = tmp->next;
	}
	if (!(tmp = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	tmp->s = ft_strnew(0);
	tmp->fdc = fd;
	tmp->next = (*h);
	(*h) = tmp;
	return (&(tmp->s));
}

int		func_for_chkstr(char **s, char **line, int i)
{
	char *trash;

	trash = *s;
	if ((*s)[i] == '\n')
	{
		if (!(*line = ft_strsub(*s, 0, (unsigned int)i)))
			return (-1);
	}
	else if (!(*line = ft_strdup(*s)))
		return (-1);
	if (!(*s = ft_strsub(trash, (unsigned int)i + 1, (ft_strlen(*s) - i))))
		return (-1);
	ft_strdel(&trash);
	return (1);
}

int		chkstr(char **s, char **line, int c)
{
	int i;

	i = -1;
	while ((*s)[++i])
		if ((*s)[i] == '\n')
			return (func_for_chkstr(s, line, i));
	if (**s && !c)
		return (func_for_chkstr(s, line, i));
	return (0);
}

int		func_for_gnl(char **s, char *tmp, char **line, const int fd)
{
	int		r;
	char	*trash;

	if (!ft_strchr(*s, '\n'))
		while (read(fd, tmp, BUFF_SIZE))
		{
			trash = *s;
			if (!(*s = ft_strjoin(trash, tmp)))
			{
				ft_strdel(&tmp);
				return (-1);
			}
			ft_strdel(&trash);
			if ((r = chkstr(&(*s), line, 1)))
			{
				ft_strdel(&tmp);
				return (r);
			}
			ft_strclr(tmp);
		}
	if ((r = chkstr(&(*s), line, 0)))
		return (r);
	ft_strdel(&tmp);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*head;
	char			*tmp;
	char			**s;

	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL ||
		!(tmp = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((read(fd, tmp, 0) < 0))
	{
		ft_strdel(&tmp);
		return (-1);
	}
	s = create_and_find_list(&head, fd);
	return (func_for_gnl(s, tmp, line, fd));
}
