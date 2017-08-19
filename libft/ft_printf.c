/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:24:11 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:24:33 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_strclear(char **s, char **str)
{
	if (*s && ft_strcmp(*s, "0"))
	{
		*str = *s;
		ft_strdel(s);
	}
	else
		*str = *s;
}

void		skip_flags_length_type(char **s, t_prntf *bs)
{
	while (**s && (check_flags(**s) || check_length(**s) || ft_isdigit(**s)
		|| bs->tp == **s))
	{
		if (bs->tp != 0 && bs->tp == **s)
		{
			(*s)++;
			break ;
		}
		(*s)++;
	}
}

static void	check_valist(char *s, va_list ap, t_prntf *bs)
{
	while (*s && (check_afte_pers(*s) || ft_isdigit(*s)))
		s++;
	if (check_type(*s))
		bs->nbr = va_arg(ap, void *);
	else
	{
		if (*s)
		{
			bs->tp = *s;
			bs->nbr = (void *)(size_t)(*s);
		}
	}
}

static void	new_main(char *format, t_prntf *bs, va_list ap)
{
	while (*format)
	{
		print_symbol(&format, bs);
		if (*format == '%')
		{
			format++;
			fill_flags(format, bs);
			fill_digit(format, bs, ap);
			fill_type(format, &bs->tp);
			fill_modificator(format, &bs->mdf);
			fill_priority(&bs);
			fill_bitoa(bs->tp, &bs->bfita);
			check_valist(format, ap, bs);
			skip_flags_length_type(&format, bs);
			print(bs);
			fill_basetoziro(bs);
		}
	}
}

int			ft_printf(char *format, ...)
{
	va_list ap;
	t_prntf bs;

	bs.r = 0;
	va_start(ap, format);
	fill_basetoziro(&bs);
	new_main(format, &bs, ap);
	va_end(ap);
	return (bs.r);
}
