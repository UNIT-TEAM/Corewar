/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cast_pdi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 11:04:11 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/15 11:04:20 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cast_di(t_prntf *bs)
{
	char *s;

	s = "";
	if (bs->mdf == 0 && bs->tp != 'D')
		s = ft_itoa_b((int)(bs->nbr), 10);
	else if (bs->mdf == 'H' && bs->tp != 'D')
		s = ft_itoa_b((signed char)(bs->nbr), 10);
	else if (bs->mdf == 'h' && bs->tp != 'D')
		s = ft_itoa_b((short)(bs->nbr), 10);
	else if (bs->mdf == 'l')
		s = ft_itoa_b((long)(bs->nbr), 10);
	else if (bs->mdf != 'L' && bs->mdf != 'j' && bs->mdf != 'z' &&
			bs->tp == 'D')
		s = ft_itoa_b((long)(bs->nbr), 10);
	else if (bs->mdf == 'L')
		s = ft_itoa_b((long long)(bs->nbr), 10);
	else if (bs->mdf == 'j' || bs->mdf == 'z')
		s = ft_itoa_b((intmax_t)(bs->nbr), 10);
	ft_strclear(&s, &bs->str);
}

void	cast_uox(t_prntf *bs)
{
	char	*s;
	char	c;

	s = "";
	c = bs->tp;
	if (bs->mdf == 0 && c != 'U' && c != 'O')
		s = ft_itoab_u((unsigned int)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'H' && c != 'U' && c != 'O')
		s = ft_itoab_u((unsigned char)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'h' && c != 'U' && c != 'O')
		s = ft_itoab_u((unsigned short)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'l')
		s = ft_itoab_u((unsigned long)(bs->nbr), bs->bfita, c);
	else if ((bs->mdf != 'L' && bs->mdf != 'j' && bs->mdf != 'z') &&
			(c == 'O' || c == 'U'))
		s = ft_itoab_u((unsigned long)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'L')
		s = ft_itoab_u((unsigned long long)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'j')
		s = ft_itoab_u((uintmax_t)(bs->nbr), bs->bfita, c);
	else if (bs->mdf == 'z')
		s = ft_itoab_u((size_t)(bs->nbr), bs->bfita, c);
	ft_strclear(&s, &bs->str);
}

void	print_p(t_prntf *bs)
{
	char *s;

	s = ft_itoab_u((unsigned long int)(bs->nbr), 16, 'x');
	if (s && ft_strcmp(s, "0"))
	{
		bs->str = s;
		ft_strdel(&s);
	}
	else
		bs->str = s;
	if (bs->prc != -1)
		print_prc(bs);
	if (bs->z && !bs->m && bs->prc == -1)
		print_aka_flags(1, 'x', bs);
	(bs->nw != 0 && !bs->m && bs->prc == -1) ? print_width(bs, 2, 0) : 0;
	if (!bs->z && bs->prc == -1)
		print_aka_flags(1, 'x', bs);
	if (bs->prc == -1)
		print_aka_flags(1, 'p', bs);
	(bs->m && bs->prc == -1) ? print_width(bs, 2, 0) : 0;
}

void	print_di_m(t_prntf *bs)
{
	(bs->nw != 0 && !bs->m && bs->z == 0) ? print_width(bs, 0, 0) : 0;
	if (bs->m)
		print_aka_flags(1, 'p', bs);
	(bs->m) ? print_width(bs, 0, 0) : 0;
	if (!bs->m)
	{
		(bs->z) ? write(1, "-", 1) : 0;
		(bs->z) ? print_width(bs, 0, 0) : 0;
		(bs->z) ? ft_putstr(bs->str + 1) : 0;
		(!bs->z) ? ft_putstr(bs->str) : 0;
		bs->r += ft_strlen((bs)->str);
	}
}

void	print_di(t_prntf *bs)
{
	cast_di(bs);
	if (bs->spc && check_minus_in_type(*(bs->str)))
		bs->spc = 0;
	if (bs->prc != -1 && !check_minus_in_type(*(bs->str)))
		print_prc(bs);
	if (bs->prc != -1 && check_minus_in_type(*(bs->str)))
		print_prc_m(bs);
	else if (check_minus_in_type(*(bs->str)) && bs->prc == -1)
		print_di_m(bs);
	else if (bs->prc == -1)
	{
		(bs->spc) ? print_aka_flags(1, ' ', bs) : 0;
		(bs->z && bs->pls) ? print_aka_flags(1, '+', bs) : 0;
		if (bs->nw != 0 && !bs->m)
			(bs->pls) ? print_width(bs, 1, 0) : print_width(bs, 0, 0);
		(!bs->z && bs->pls) ? print_aka_flags(1, '+', bs) : 0;
		((bs->pls && bs->m) || bs->m) ? print_aka_flags(1, 'p', bs) : 0;
		if (bs->m)
			(bs->pls) ? print_width(bs, 1, 0) : print_width(bs, 0, 0);
		((bs->pls && !bs->m) || !bs->m) ? print_aka_flags(1, 'p', bs) : 0;
	}
}
