/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prec_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:15:14 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 15:15:22 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** function for printing '0', ' ', '+', '0X', '0x', '-'.
** wl - only for loop
** 'p' for write string using ft_putstr
*/

void		print_aka_flags(int wl, char c, t_prntf *bs)
{
	if (c == '0' || c == ' ')
		while (wl-- > 0)
		{
			write(1, &c, 1);
			bs->r++;
		}
	else if (c == '+' || c == '-')
	{
		write(1, &c, 1);
		bs->r++;
	}
	else if (c == 'X' || c == 'x')
	{
		write(1, "0", 1);
		write(1, &c, 1);
		bs->r += 2;
	}
	else if (c == 'p')
	{
		ft_putstr(bs->str);
		bs->r += ft_strlen(bs->str);
	}
}

/*
** additional function for main function print_prc.
** When minus not is present
*/

static void	for_print_prc(int l, int w, t_prntf *bs)
{
	print_aka_flags(l, ' ', bs);
	if (bs->hash && (bs->tp == 'o' || bs->tp == 'O'))
		print_aka_flags(1, '0', bs);
	if ((bs->hash && ft_strcmp(bs->str, "0") && bs->tp == 'x') || bs->tp == 'p')
		print_aka_flags(1, 'x', bs);
	if (bs->hash && (bs->tp == 'X') && ft_strcmp(bs->str, "0"))
		print_aka_flags(1, 'X', bs);
	if (bs->pls && (bs->tp == 'd' || bs->tp == 'D' || bs->tp == 'i'))
		print_aka_flags(1, '+', bs);
	print_aka_flags(w, '0', bs);
	(!ft_strcmp(bs->str, "0")) ? 0 : ft_putstr(bs->str);
	if (ft_strcmp(bs->str, "0"))
		bs->r += ft_strlen(bs->str);
}

/*
** additional function for main function print_prc.
** When minus is present
*/

static void	for_print_prc_m(int l, int w, t_prntf *bs)
{
	if (bs->spc && (bs->tp == 'd' || bs->tp == 'D' || bs->tp == 'i'))
		print_aka_flags(1, ' ', bs);
	if (bs->pls && (bs->tp == 'd' || bs->tp == 'D' || bs->tp == 'i'))
		print_aka_flags(1, '+', bs);
	if (bs->hash && (bs->tp == 'o' || bs->tp == 'O'))
		print_aka_flags(1, '0', bs);
	if (bs->hash && (bs->tp == 'x') && ft_strcmp(bs->str, "0"))
		print_aka_flags(1, 'x', bs);
	if (bs->hash && (bs->tp == 'X') && ft_strcmp(bs->str, "0"))
		print_aka_flags(1, 'X', bs);
	if (bs->tp == 'p')
		print_aka_flags(1, 'x', bs);
	print_aka_flags(w, '0', bs);
	(!ft_strcmp(bs->str, "0")) ? 0 : ft_putstr(bs->str);
	if (ft_strcmp(bs->str, "0"))
		bs->r += ft_strlen(bs->str);
	(bs->spc && (bs->tp == 'd' || bs->tp == 'D' || bs->tp == 'i')) ? l-- : 0;
	print_aka_flags(l, ' ', bs);
}

/*
** function for print precision
*/

void		print_prc(t_prntf *bs)
{
	int l;
	int w;
	int p;

	p = (!ft_strcmp(bs->str, "0")) ? 0 : (int)ft_strlen(bs->str);
	w = (p >= bs->prc) ? 0 : bs->prc - p;
	if (!ft_strcmp(bs->str, "0"))
		l = (p >= bs->nw) ? 0 : (bs->nw - w);
	else
		l = (p >= bs->nw) ? 0 : (int)(bs->nw - w - (ft_strlen(bs->str)));
	(bs->hash && w != 0 && (bs->tp == 'o' || bs->tp == 'O')) ? w-- : 0;
	(bs->hash && (bs->tp == 'o' || bs->tp == 'O') && w == 0) ? l-- : 0;
	(bs->pls && (bs->tp == 'd' || bs->tp == 'D' || bs->tp == 'i')) ? l-- : 0;
	(bs->hash && ft_strcmp(bs->str, "0") && (bs->tp == 'x' ||
		bs->tp == 'X')) ? l = l - 2 : 0;
	(bs->tp == 'p') ? l = l - 2 : 0;
	if (!bs->m)
		for_print_prc(l, w, bs);
	if (bs->m)
		for_print_prc_m(l, w, bs);
}

/*
** function for print precision when argument is negative
*/

void		print_prc_m(t_prntf *bs)
{
	int l;
	int w;
	int p;

	p = (int)ft_strlen(bs->str);
	w = (p >= bs->prc) ? 0 : bs->prc - p;
	l = (p >= bs->nw) ? 0 : (int)(bs->nw - w - (ft_strlen(bs->str)));
	(p > bs->prc) ? 0 : w++;
	(p > bs->prc) ? 0 : l--;
	if (!bs->m)
	{
		print_aka_flags(l, ' ', bs);
		print_aka_flags(1, '-', bs);
		print_aka_flags(w, '0', bs);
		ft_putstr(bs->str + 1);
		bs->r += ft_strlen(bs->str + 1);
	}
	if (bs->m)
	{
		print_aka_flags(1, '-', bs);
		print_aka_flags(w, '0', bs);
		ft_putstr(bs->str + 1);
		bs->r += ft_strlen(bs->str + 1);
		print_aka_flags(l, ' ', bs);
	}
}
