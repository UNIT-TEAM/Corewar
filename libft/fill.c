/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:08:36 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:11:55 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_precision(char **s, int *prc, va_list ap)
{
	*prc = 0;
	(**s && !check_type(**s)) ? (*s)++ : 0;
	if (**s == '*')
	{
		*prc = va_arg(ap, int);
		if (*prc < 0)
			*prc = -1;
		(*s)++;
	}
	if (**s != '*')
	{
		while (ft_isdigit(**s))
		{
			if (*prc == -1)
				*prc = *prc + ((**s) - '0' + 1);
			else
				*prc = *prc + ((**s) - '0');
			if (ft_isdigit(*(*s + 1)))
				*prc *= 10;
			(*s)++;
		}
	}
}

void		fill_digit(char *s, t_prntf *bs, va_list ap)
{
	while (*s && (check_flags(*s) || ft_isdigit(*s) || check_length(*s)))
	{
		(*s == '0') ? bs->z = 1 : 0;
		if (*s == '*')
		{
			bs->nw = va_arg(ap, int);
			if (bs->nw < 0 && (bs->m = 1))
				bs->nw *= -1;
			s++;
		}
		if (isdigit_withoutziro(*s))
		{
			bs->nw = 0;
			while (ft_isdigit(*s))
			{
				bs->nw = bs->nw + ((*s) - '0');
				if (ft_isdigit(*(s + 1)))
					bs->nw *= 10;
				s++;
			}
		}
		(*s == '.') ? fill_precision(&s, &bs->prc, ap) : 0;
		(*s && !check_type(*s) && *s != '*' && *s != '.') ? s++ : 0;
	}
}

void		fill_flags(char *s, t_prntf *bs)
{
	while (*s && (check_afte_pers(*s) || ft_isdigit(*s)))
	{
		(*s == ' ') ? bs->spc = 1 : 0;
		(*s == '+') ? bs->pls = 1 : 0;
		(*s == '-') ? bs->m = 1 : 0;
		(*s == '#') ? bs->hash = 1 : 0;
		s++;
	}
}

void		fill_basetoziro(t_prntf *bs)
{
	bs->nw = 0;
	bs->m = 0;
	bs->pls = 0;
	bs->z = 0;
	bs->hash = 0;
	bs->spc = 0;
	bs->nbr = 0;
	bs->tp = 0;
	bs->mdf = 0;
	bs->str = "";
	bs->prc = -1;
	bs->bfita = 0;
}
