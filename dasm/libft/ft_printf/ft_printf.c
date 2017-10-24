/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:41:21 by ysalata           #+#    #+#             */
/*   Updated: 2017/06/10 18:22:08 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				str_error(t_spesif *spec, int *retval)
{
	char		*msg;
	int			i;

	i = 0;
	msg = "(null)";
	if (spec->ac < i)
	{
		if (spec->ac == -2)
			while (spec->width-- > 0)
				ft_write((spec->zero ? "0" : " "), ++(*retval));
		else
			while (msg[i])
				ft_write(&msg[i++], ++(*retval));
	}
	else
		while (spec->ac > i)
			ft_write(&msg[i++], ++(*retval));
	return (1);
}

void			create_flags(t_func *tflag)
{
	tflag->fun['D'] = &s_decimal;
	tflag->fun['d'] = &s_decimal;
	tflag->fun['i'] = &s_decimal;
	tflag->fun['O'] = &s_unsig;
	tflag->fun['U'] = &s_unsig;
	tflag->fun['o'] = &s_unsig;
	tflag->fun['u'] = &s_unsig;
	tflag->fun['x'] = &s_unsig;
	tflag->fun['X'] = &s_unsig;
	tflag->fun['b'] = &s_unsig;
	tflag->fun['p'] = &s_unsig;
	tflag->fun['c'] = &s_char;
	tflag->fun['C'] = &s_char;
	tflag->fun['s'] = &s_string;
	tflag->fun['S'] = &s_string;
	tflag->fun['n'] = &s_n;
}

int				read_format(t_format *tform, char *format, va_list *ap)
{
	t_func		tflag;

	tform->i_pos = -1;
	tform->retval = 0;
	create_flags(&tflag);
	tform->len = (int)ft_strlen(format);
	while (++(tform->i_pos) < tform->len)
		if (format[tform->i_pos] == '%')
		{
			if (format[++tform->i_pos] == '%')
				ft_write("%", ++tform->retval);
			else if (format[tform->i_pos])
				parse_line(&tflag, tform, format, ap);
			else
				break ;
		}
		else
			ft_write(&format[tform->i_pos], ++tform->retval);
	return (0);
}

/*
** FT_PRINTF == main func
*/

int				ft_printf(char *format, ...)
{
	va_list		ap;
	t_format	tform;

	if (!format)
		return (0);
	tform.i_pos = -1;
	va_start(ap, format);
	read_format(&tform, format, &ap);
	va_end(ap);
	return (tform.retval);
}
