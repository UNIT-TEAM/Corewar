/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:17:33 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/24 07:59:56 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

#define RE REG_NUMBER

char	*g_l;

int			cw_check_value(t_cmnd *cmnd, int j, char *label, int t)
{
	int i;

	i = 0;
	cmnd->cipher |= t ? DIR_CODE : IND_CODE;
	cmnd->size += (t && !g_tab[cmnd->cmd].id2) ? 4 : 2;
	if (j + 1 == g_tab[cmnd->cmd].arg)
		if (!cw_write_cmd(cmnd, j, 0))
			return (cw_e(27));
	if (IS_LBL(label[i]))
		return (0);
	cmnd->args[j][i] == '%' ? i++ : 0;
	cmnd->args[j][i] == '-' ? i++ : 0;
	if (!(ft_isaldigit(cmnd->args[j] + i)))
		return (cw_e(20));
	cmnd->i_arg[j] = (UI)ft_atoi(label);
	if (t && !g_tab[cmnd->cmd].id2)
	{
		cmnd->i_arg[j] = ((cmnd->i_arg[j] << 8) & 0xFF00FF00) | 	\
			((cmnd->i_arg[j] >> 8) & 0xFF00FF);
		cmnd->i_arg[j] = SWAP_UI(cmnd->i_arg[j]);
	}
	else
		cmnd->i_arg[j] = SWAP_USI(cmnd->i_arg[j]);
	return (0);
}

int			cw_write_cmd(t_cmnd *cmnd, int type, int i)
{
	int		j;

	if (type >= 0)
	{
		g_l = cmnd->args[type];
		g_l[i] == '%' ? ++i : 0;
		g_l[i] == ':' ? i++ : 0;
		g_l[i] == '-' ? i++ : 0;
		while (!IS_COM(g_l[i]) && g_l[i] && !SPACE(g_l[i]))
			i++;
		j = i;
		if (g_l[i])
		{
			while (g_l[i] && SPACE(g_l[i]))
				i++;
			if (g_l[i] && !IS_COM(g_l[i]))
				return (0);
		}
		cmnd->args[type] = ft_strsub(g_l, 0, (size_t)j);
		ft_strdel(&g_l);
		return (1);
	}
	cmnd->size++;
	g_tab[cmnd->cmd].id1 ? cmnd->size++ : 0;
	return (1);
}

/*
** parse all(i) args(arg) in command line(cmnd)
** checking if all arguments matched their required types
*/

int			cw_args_parse(int i, char *arg, t_cmnd *cmnd)
{
	int		error;

	error = 0;
	if (!arg[0])
		return (cw_e(18));
	cmnd->cipher <<= 2;
	if ((g_tab[cmnd->cmd].kind[i] & T_REG) && arg[0] == 'r' && arg[1])
	{
		g_file->cmnd->cipher |= REG_CODE;
		g_file->cmnd->i_arg[i] = (UI)ft_atoi(arg + 1);
		if (!ft_isaldigit(arg + 1) || g_file->cmnd->i_arg[i] > RE || \
			g_file->cmnd->i_arg[i] < 1)
			return (cw_e(19));
		cmnd->size += T_REG;
	}
	else if ((g_tab[cmnd->cmd].kind[i] & T_DIR) && IS_DIR(arg[0]))
		error = cw_check_value(cmnd, i, (arg + 1), 1);
	else if ((g_tab[cmnd->cmd].kind[i] & T_IND))
		error = cw_check_value(cmnd, i, arg, 0);
	else
		return (cw_e(20));
	if (!error && ++i)
		return (i != g_tab[cmnd->cmd].arg ? \
				cw_args_parse(i, g_file->cmnd->args[i], g_file->cmnd) : 1);
		return (-13);
}

/*
** Initialize new command variables
*/

t_cmnd		*cw_cmnd_init(int *i)
{
	t_cmnd	*c;

	c = (t_cmnd *)malloc(sizeof(t_cmnd));
	if (g_i == 0)
		while (g_s[g_i] && SPACE(g_s[g_i]))
			g_i++;
	while (g_s[g_i + (*i)] && !SPACE(g_s[g_i + (*i)]))
		(*i)++;
	c->name = ft_strsub(g_s + g_i, 0, (size_t)(*i));
	c->line = g_file->lines;
	c->start = g_bytes;
	c->size = 0;
	c->cmd = -1;
	c->cipher = 0;
	return (c);
}

/*
** adding new command
** TODO: add skip comment after command line
*/

int			cw_cmd(int i, int j, int cmd, int k)
{
	t_cmnd	*c;

	k ? g_i = 0 : 0;
	c = cw_cmnd_init(&i);
	while (++cmd < 16)
		if (!ft_strcmp(g_tab[cmd].op, c->name))
			c->cmd = cmd;
	if (c->cmd == -1)
		return (cw_e(16));
	c->args = ft_strsplit(g_s + g_i + i, SEPARATOR_CHAR);
	while (c->args[++j])
	{
		g_l = ft_strtrim(c->args[j]);
		ft_strdel(&c->args[j]);
		c->args[j] = g_l;
	}
	if (j != g_tab[c->cmd].arg || g_s[ft_strlen(g_s) - 1] == ',')
		return (cw_e(17));
	c->next = g_file->cmnd ? g_file->cmnd : NULL;
	g_file->cmnd ? g_file->cmnd->prev = c : NULL;
	g_file->cmnd = c;
	if (cw_args_parse(0, g_file->cmnd->args[0], g_file->cmnd) <= 0)
		return (-1);
	cw_write_cmd(g_file->cmnd, -1, 0);
	return (g_bytes += g_file->cmnd->size);
}
