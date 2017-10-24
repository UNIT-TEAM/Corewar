/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:00:56 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/20 18:07:28 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			cw_check_end(int i)
{
	char	c;

	lseek(g_fd, -1, SEEK_END);
	read(g_fd, &c, 1);
	if (c == '\n')
		return (1);
	while (c != '\n')
	{
		if (lseek(g_fd, -i, SEEK_END) == -1L)
			return (0);
		read(g_fd, &c, 1);
		i++;
	}
	while (!IS_COM(c) && SPACE(c) || c == '\n')
		if (!read(g_fd, &c, 1))
			return (1);
	return (IS_COM(c) ? 1 : 0);
}

/*
** Cleaning trash function(after .name && .comment)
*/

int			cw_head_clean(int type, int i, int j)
{
	char	*s;

	s = type ? g_file->name : g_file->comm;
	while (s[i] && s[i] != '\"')
		i++;
	j = i;
	while (s[++j] && !IS_COM(s[j]))
		if (!SPACE(s[j]))
			return (type ? cw_e(23) : cw_e(24));
	if (type)
	{
		g_file->name[i] = '\0';
		if (ft_strlen(g_file->name) > PROG_NAME_LENGTH)
			return (cw_e(12));
		else
			ft_bzero(g_head->prog_name, PROG_NAME_LENGTH + 1);
		ft_strncpy(g_head->prog_name, g_file->name, ft_strlen(g_file->name));
		return (cw_head_clean(0, 0, 0));
	}
	g_file->comm[i] = '\0';
	if (ft_strlen(g_file->comm) > COMMENT_LENGTH)
		return (cw_e(13));
	ft_bzero(g_head->comment, COMMENT_LENGTH + 1);
	ft_strncpy(g_head->comment, g_file->comm, ft_strlen(g_file->comm));
	return (1);
}

/*
** Parsing HEADER(.comment && .name)
*/

int			cw_head_parse(int i, char *dst, char *str, int type)
{
	while (str[i] && SPACE(str[i]))
		i++;
	if (!str[i])
		return (cw_e(8));
	if (str[i++] != '\"')
		return (cw_e(9));
	dst = ft_strdup(str + i);
	while (!ft_strchr(dst, '\"'))
	{
		dst = ft_strjoin(dst, "\n");
		g_file->lines++;
		if (get_next_line(g_fd, &str) < 1)
			return (cw_e(10));
		(dst = ft_strjoin(dst, str)) ? ft_strdel(&str) : 0;
	}
	if (type)
		g_file->comm = dst;
	else
		g_file->name = dst;
	return (1);
}

/*
** Reading HEADER(.comment && .name)
*/

int			cw_read_head(int error)
{
	if (!ft_strncmp(g_s + g_i, NAME, ft_strlen(NAME)))
	{
		if (g_file->name != NULL)
			return (cw_e(4));
		g_i += ft_strlen(NAME);
		error = cw_head_parse(0, g_file->name, g_s + g_i, 0);
	}
	else if (!ft_strncmp(g_s + g_i, C, ft_strlen(C)))
	{
		if (g_file->comm != NULL)
			return (cw_e(5));
		g_i += ft_strlen(C);
		error = cw_head_parse(0, g_file->comm, g_s + g_i, 1);
	}
	else
		return (!g_file->name ? cw_e(6) : cw_e(7));
	if (error < 0)
		return (-42);
	return (!g_file->name || !g_file->comm ? 0 : cw_head_clean(1, 0, 0));
}
