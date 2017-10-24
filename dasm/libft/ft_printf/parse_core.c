/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 18:18:22 by ysalata           #+#    #+#             */
/*   Updated: 2017/04/21 17:07:01 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Function for check the modifictor
** 1 - hh | 2 - h | 3 - l | 4 - L | 5 - ll | 6 - j | 7 - z
*/

static void			check_modif(char *format, int *i_pos, int *mod)
{
	int				buf;

	if (format[*i_pos] != format[++(*i_pos)])
	{
		if (format[*i_pos - 1] == 'h')
			buf = 2;
		else if (format[*i_pos - 1] == 'l')
			buf = 3;
		else if (format[*i_pos - 1] != 'L')
			buf = (format[*i_pos - 1] == 'j') ? 6 : 7;
		else
			buf = 4;
	}
	else
		buf = (format[++(*i_pos) - 1] == 'h') ? 1 : 5;
	(buf > *mod) ? *mod = buf : 0;
}

/*
** Searching for flags, width && accuracy, modificators before type char
** Return == 0 ? ALL OKAY : underfind behavior
*/

static void			check_flag(t_spesif *s, char *format, int *i_pos, int len)
{
	int				i;

	i = *i_pos - 1;
	while (ft_strchr("-+ #0", format[++i]) && i < len)
	{
		(format[i] == '-') ? (s->m = '-') : FALSE;
		(format[i] == '+') ? (s->plus = '+') : FALSE;
		(!s->plus && format[i] == ' ') ? (s->space = TRUE) : 0;
		(format[i] == '#') ? (s->hash = TRUE) : FALSE;
		(!s->m && format[i] == '0') ? (s->zero = TRUE) : FALSE;
	}
	*i_pos = i;
	s->znak = (s->plus || s->space) ? TRUE : FALSE;
}

static void			obnull_yay(t_format *tform, t_spesif *spec, \
	char *f)
{
	if (ft_isdigit(f[tform->i_pos]) || f[tform->i_pos] == '*')
		spec->width = 0;
	if (f[tform->i_pos] == '.' && tform->i_pos++)
		spec->ac = 0;
}

/*
** Check Width AND ACcuracy
*/

static void			check_wandac(t_spesif *s, char *f, \
	int *i_pos, va_list *ap)
{
	if (f[(*i_pos - 1)] != '.')
		while (ft_isdigit(f[*i_pos]) || f[*i_pos] == '*')
		{
			if (((f[*i_pos] != '*') ? (s->width += (f[*i_pos] -\
				'0')) : 0) || (f[*i_pos] != '*'))
				s->width *= ft_isdigit(f[++(*i_pos)]) ? 10 : 1;
			else if (((s->width = va_arg(*ap, int)) || !s->width) \
					&& ++(*i_pos))
				break ;
		}
	else
		while (ft_isdigit(f[*i_pos]) || f[*i_pos] == '*')
		{
			if (((f[*i_pos] != '*') ? s->ac += (f[*i_pos]\
				- '0') : 0) || (f[*i_pos] != '*'))
				s->ac *= ft_isdigit(f[++(*i_pos)]) ? 10 : 1;
			else if ((s->ac >= 0 && ((s->ac = va_arg(*ap, int)) ||\
				!s->ac)) && ++(*i_pos))
				break ;
		}
	little_check(s, f, i_pos);
}

/*
**	Main parse core of the ft_printf, returns 1
** 	ALWAYS RETURNS 1!! ¯ \ _ (ツ) _ / ¯
*/

int					parse_line(t_func *flags, t_format *tform,
						char *f, va_list *ap)
{
	t_spesif	s;

	create_srtuct(&s);
	while (ft_strchr("+-#* 0123456789hzjlL.", f[tform->i_pos]))
	{
		check_flag(&s, f, &(tform->i_pos), tform->len);
		obnull_yay(tform, &s, f);
		check_wandac(&s, f, &(tform->i_pos), ap);
		if (ft_strchr("jzhlL", f[tform->i_pos]))
			check_modif(f, &(tform->i_pos), &s.modif);
		if (tform->i_pos > tform->len)
			return (0);
	}
	ft_strchr("DOUS", f[tform->i_pos]) ? s.modif = 3 : 0;
	if ((f[tform->i_pos] == 'p') ? s.hash = TRUE : 0)
		if ((s.type = 'w'))
			s.modif = 3;
	s.type = *ft_kstrchr("dDbiuUoOxXcCsSpn", f[tform->i_pos]);
	if ((s.type == 'K') ? s.lol = f[tform->i_pos] : 0)
		flags->fun[(int)'c'](ap, tform, &s);
	else
		flags->fun[(int)(f[tform->i_pos])](ap, tform, &s);
	return (1);
}
