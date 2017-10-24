/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:14:16 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/24 07:53:40 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** Final command write here:
*/

void		cw_write_code(t_cmnd *tmp, int fd)
{
	int		i;
	char	k;
	int		type;

	while (tmp)
	{
		i = 1;
		k = tmp->cipher << ((4 - g_tab[tmp->cmd].arg) * 2);
		write(fd, &g_tab[tmp->cmd].num, 1);
		g_tab[tmp->cmd].id1 == 1 ? write(fd, &(k), 1) : 0;
		while (i <= g_tab[tmp->cmd].arg)
		{
			type = tmp->cipher >> (g_tab[tmp->cmd].arg - i) * 2;
			type &= 3;
			if (type == 1)
				write(fd, &(tmp->i_arg[i - 1]), 1);
			else if (type == 2 && !g_tab[tmp->cmd].id2)
				write(fd, &(tmp->i_arg[i - 1]), 4);
			else if (type == 3 || type == 2)
				write(fd, &(tmp->i_arg[i - 1]), 2);
			i++;
		}
		tmp = tmp->prev;
	}
}

int			cw_write_all(char *name, t_cmnd *tmp)
{
	char	*new;
	char	*buf;
	int		fd;

	g_head->prog_size = cw_endian(g_bytes);
	g_head->magic = cw_endian(COREWAR_EXEC_MAGIC);
	if (g_file->cmnd == NULL)
		return (cw_e(25));
	new = ft_strsub(name, 0, ft_strlen(name) - 2);
	buf = new;
	new = ft_strjoin(buf, ".cor");
	ft_strdel(&buf);
	if ((fd = open(new, O_RDWR | O_CREAT, 00700)) < 0)
		return (cw_e(26));
	write(fd, g_head, sizeof(t_header));
	while (tmp->next)
		tmp = tmp->next;
	cw_write_code(tmp, fd);
	close(fd);
	return (1);
}
