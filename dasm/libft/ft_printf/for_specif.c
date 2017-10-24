/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_specif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:56:05 by ysalata           #+#    #+#             */
/*   Updated: 2017/04/21 17:52:09 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FOR POINTER SPECIFICATOR: n.
*/

void		s_n(va_list *ap, t_format *tform, t_spesif *spec)
{
	long long int *i;

	i = tsize_n(spec->modif, *ap);
	*i = tform->retval;
}

/*
** FOR CHAR SPECIFICATORS: c,C && if no specif was founded.
*/

void		s_char(va_list *ap, t_format *tform, t_spesif *spec)
{
	if (spec->type == 'K')
		spec->slen.c = spec->lol;
	else
		spec->slen.c = (unsigned char)va_arg(*ap, int);
	spec->len = ((1 >= spec->ac) ? 1 : (spec->ac));
	if (!spec->m && (spec->width > 1) && !spec->zero)
		while (--spec->width >= 1)
			ft_write(" ", ++tform->retval);
	if (!spec->m && (spec->width > 1))
		while (--spec->width >= 1)
			ft_write("0", ++tform->retval);
	(spec->lol == '%') ? ft_write("%", ++tform->retval) : 0;
	(spec->lol != '%') ? ft_write(&spec->slen.c, ++tform->retval) \
		: 0;
	if (spec->m && (spec->width > 0))
		while (spec->width-- > spec->len)
			ft_write(" ", ++tform->retval);
}

/*
** FOR STRING SPECIFICATORS: s,S.
*/

void		s_string(va_list *ap, t_format *tform, t_spesif *s)
{
	int		len;

	len = 0;
	if ((s->modif == 3) ? s->slen.ls = va_arg(*ap, wchar_t *) : 0)
		len = (int)ft_wstrlen(s->slen.ls);
	else if (s->modif != 3 && (s->slen.s = va_arg(*ap, char *)))
		len = (int)ft_strlen(s->slen.s);
	else if (str_error(s, &tform->retval))
		return ;
	s->len = ((len >= s->ac && s->ac != -1) ? s->ac : len);
	if (!s->m && (s->width > s->len) && !s->zero)
		while (--s->width >= s->len && s->width >= 0)
			ft_write(" ", ++tform->retval);
	if (!s->m && (s->width > s->len))
		while (--s->width >= s->len && s->width >= 0)
			ft_write("0", ++tform->retval);
	(s->ac != -2 && s->modif != 3) ? \
		ft_swrite(s->slen.s, tform, s->len) : 0;
	(s->ac != -2 && s->modif == 3) ? \
		ft_lswrite(s->slen.ls, tform, s->len, 0) : 0;
	if (s->m && (s->width > 0))
		while (s->width-- > s->len)
			ft_write(" ", ++tform->retval);
}

/*
** FOR SPECIFICATORS: u,U,o,O,x,X,b,p.
*/

void		s_unsig(va_list *ap, t_format *tform, t_spesif *s)
{
	char	*buf;
	int		base;

	base = choose_sys(s->type);
	s->num = tsize_uns(s->modif, *ap);
	buf = ft_unitoabase((unsigned long long)s->num, base, s->lick);
	s->len = ft_checkstr(buf, s, base);
	if (!s->m && (s->width > s->len) && !s->zero)
		while (s->width-- > s->len)
			ft_write(" ", ++tform->retval);
	if (s->hash && base != 10 && base != 2)
		(s->type != 'p' && s->num == 0 && (s->ac != -2 || base == 16)) ?\
			0 : ft_write("0", ++tform->retval);
	if (s->hash && base == 16 && (s->num != 0 || s->type == 'p'))
		(s->type != 'p') ? ft_write(&s->type, ++tform->retval) :\
			ft_write("x", ++tform->retval);
	if ((s->zero && (s->ac <= 0) && !s->m) && (s->width > s->len))
		while (s->width-- > s->len + s->znak)
			ft_write("0", ++tform->retval);
	while (s->ac > ((int)ft_strlen(buf) + s->znak) && s->ac-- >= 0)
		ft_write("0", ++tform->retval);
	(s->ac == -2 && s->num == 0) ? 0 : prf_putstr(buf, &(tform->retval));
	if (s->m && (s->width > 0))
		while (s->width-- > s->len)
			ft_write(" ", ++tform->retval);
}

/*
** FOR DECIMAL SPECIFICATORS: d,I,ac,I.
*/

void		s_decimal(va_list *ap, t_format *tform, t_spesif *s)
{
	char	*buf;
	int		len;

	if (!((s->num = tsize_dec(s->modif, *ap))))
		s->num = 0;
	(s->num < 0) ? (s->znak = 1) : FALSE;
	buf = ft_itoabase(s->num, 10, s->lick);
	len = (s->ac == -2 && s->num == 0) ? 0 : (int)ft_strlen(buf);
	s->len = ((len >= s->ac) ? len : (s->ac));
	if (!s->m && (s->width > (s->len + s->znak)) && (!s->zero || (s->ac != -1)))
		while (s->width-- > (s->len + s->znak))
			ft_write(" ", ++tform->retval);
	if ((s->plus || s->space) && s->num >= 0)
		ft_write(((s->plus) ? "+" : " "), ++tform->retval);
	(s->num < 0) ? ft_write("-", ++tform->retval) : 0;
	if ((s->zero && (s->ac == -1) && !s->m) && (s->width > len))
		while (s->width-- > s->len + s->znak)
			ft_write("0", ++tform->retval);
	while (s->ac >= 0 && s->ac-- > (int)ft_strlen(buf))
		ft_write("0", ++tform->retval);
	(s->ac == -2 && s->num == 0) ? 0 : prf_putstr(buf, &(tform->retval));
	if (s->m && (s->width > 0))
		while (--s->width >= s->len + s->znak)
			ft_write(" ", ++tform->retval);
}
