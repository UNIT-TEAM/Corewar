/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:07:53 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/23 19:39:56 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			cw_calllabel(char *s, t_cmnd *c, int i, int type)
{
	t_label	*tmp;

	tmp = g_file->labl;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			c->i_arg[i] = (unsigned int)(tmp->start - c->start);
			if (!g_tab[c->cmd].id2 && type)
			{
				c->i_arg[i] = ((c->i_arg[i] << 8) & 0xFF00FF00) | \
					((c->i_arg[i] >> 8) & 0xFF00FF);
				c->i_arg[i] = SWAP_UI(c->i_arg[i]);
			}
			c->i_arg[i] = SWAP_USI(c->i_arg[i]);
			return (tmp->start - c->start);
		}
		tmp = tmp->next;
	}
	return (424242);
}

int			cw_check_label(int error)
{
	int		i;
	int		value;
	t_cmnd	*tmp;

	tmp = g_file->cmnd;
	while (tmp)
	{
		i = 1;
		while (i <= g_tab[tmp->cmd].arg && error != 424242)
		{
			value = tmp->cipher >> (g_tab[tmp->cmd].arg - i) * 2;
			value &= 3;
			if (value == 2 && IS_LBL(tmp->args[i - 1][1]))
				error = cw_calllabel(tmp->args[i - 1] + 2, tmp, i - 1, 1);
			else if (value == 3 && IS_LBL(tmp->args[i - 1][0]))
				error = cw_calllabel(tmp->args[i - 1] + 1, tmp, i - 1, 0);
			i++;
		}
		tmp = tmp->next;
		if (error == 424242)
			return (cw_e(21));
	}
	return (1);
}

/*
** Adding new label
*/

int			cw_label(int start, int len)
{
	t_label	*l;

	len = start;
	while (g_s[g_i] != LABEL_CHAR)
		g_i++;
	if (g_i == start || (g_i != 0 && (g_s[g_i - 1] == DIRECT_CHAR \
		|| SPACE(g_s[g_i - 1]) || g_s[g_i - 1] == ',')))
		return (g_i == start ? cw_e(14) : cw_cmd(0, -1, -1, 1));
	while (len < g_i)
		if (!ft_strchr(LABEL_CHARS, g_s[len++]))
			return (cw_e(15));
	l = (t_label *)malloc(sizeof(t_label));
	l->start = g_bytes;
	l->line = g_file->lines;
	l->name = ft_strsub(g_s + start, 0, (size_t)(len - start));
	l->next = g_file->labl;
	g_file->labl ? g_file->labl->prev = l : NULL;
	g_file->labl = l;
	g_i++;
	while (SPACE(g_s[g_i]))
		g_i++;
	return ((!g_s[g_i] || (IS_COM(g_s[g_i]))) ? 1 : cw_cmd(0, -1, -1, 0));
}
