/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 17:52:04 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/24 07:54:39 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** error output function
*/

int					cw_e(int type)
{
	if (type == 0)
	{
		ft_printf("Usage: ./dasm [-m] <sourcefile.s>\f");
		ft_printf("-m: Instead of creating 1 .cor, flag ./dasm can processing "
					"into the .cor all your files, those was"
					"transferred to the ./dasm argument\n");
		return (0);
	}
	ft_putstr_fd(COL_RED"error #", 2);
	ft_putnbr_fd(type, 2);
	ft_putstr_fd(g_er[type - 1], 2);
	if (type == 4 || type == 5 || type == 8 || type == 9 || type == 11	\
		|| (type > 13 && type < 22) || type == 23 || type == 24 || type == 27)
	{
		ft_putstr_fd("line  №", 2);
		ft_putnbr_fd(g_file->lines, 2);
		ft_putstr_fd(": \"", 2);
		ft_putstr_fd(g_s, 2);
		ft_putstr_fd("\"", 2);
	}
	ft_putstr_fd("\n"COL_EOC, 2);
	return (-1);
}

char				*cw_cut(char *s)
{
	int				i;
	char			*buf;

	i = 0;
	while (s[i] && !IS_COM(s[i]))
		i++;
	if (IS_COM(s[i]))
	{
		buf = ft_strsub(s, 0, (size_t)i);
		return (buf);
	}
	return (s);
}

unsigned int		cw_endian(unsigned int i)
{
	unsigned char	*us;

	us = (unsigned char*)&i;
	return (0 | (unsigned int)us[0] << 24 | (unsigned int)us[1] << 16 |
			(unsigned int)us[2] << 8 | (unsigned int)us[3]);
}

int					cw_file_analyze(int lines, char *file, int len,
									int error)
{
	g_head = (t_header *)malloc(sizeof(t_header));
	if (len < 3 || file[len - 1] != 's' || file[len - 2] != '.')
		return (cw_e(0));
	if (!cw_check_end(2))
		return (cw_e(22));
	lseek(g_fd, 0, SEEK_SET);
	g_file->lines = lines;
	while (error >= 0 && get_next_line(g_fd, &g_s) > 0 && !(g_i = 0))
	{
		ft_strchr(g_s, COMMENT_CHAR) || ft_strchr(g_s, ';') ? \
			g_s = cw_cut(g_s) : 0;
		++g_file->lines;
		while (g_s[g_i] && SPACE(g_s[g_i]))
			g_i++;
		if ((!g_s[g_i] || (IS_COM(g_s[g_i]))) && ft_strdel(&g_s))
			continue ;
		if (error > 0)
			error = (ft_strchr(g_s, LABEL) ? cw_label(g_i, 0) : \
					cw_cmd(0, -1, -1, 0));
		!error ? error = cw_read_head(0) : 0;
		ft_strdel(&g_s) ? g_i = 0 : 0;
	}
	if (error <= 0 || cw_check_label(0) < 0)
		return (error == 0 ? cw_e(3) : -1);
	return (cw_write_all(file, g_file->cmnd));
}

int					main(int ac, char **av)
{
	int				arg;
	int				bonus;

	ac < 2 || (ac == 2 && !ft_strcmp(av[1], "-m")) ? exit(cw_e(0)) : 0;
	bonus = (ac >= 2 && !ft_strcmp(av[1], "-m")) ? 2 : ac - 1;
	arg = ac;
	while (arg-- > bonus && (g_file = (t_asm *)malloc(sizeof(t_asm))))
	{
		g_i = 0;
		g_bytes = 0;
		g_s = NULL;
		g_file->name = NULL;
		g_file->comm = NULL;
		g_file->cmnd = NULL;
		g_file->labl = NULL;
		ft_printf(COL_BLUE"Start analyzing file %s\n"COL_EOC, av[arg]);
		if ((g_fd = open(av[arg], O_RDONLY)) == -1)
			return (cw_e(1));
		if (read(g_fd, g_s, 0) == -1)
			return (cw_e(2));
		if (cw_file_analyze(0, av[arg], (int)ft_strlen(av[arg]), 0) > 0)
			ft_printf(COL_GREEN".cor file was successful created!\n"COL_EOC);
		else
			ft_printf(COL_RED"Failed to create .cor file\n"COL_EOC);
	}
}
