/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:13:48 by ysalata           #+#    #+#             */
/*   Updated: 2017/05/22 18:49:44 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Dont ask me why ac -1.
** Answer: " -Cause ac want", ¯ \ _ (ツ) _ / ¯
*/

void			create_srtuct(t_spesif *spec)
{
	spec->ac = -1;
	spec->width = 0;
	spec->zero = 0;
	spec->m = 0;
	spec->plus = 0;
	spec->space = 0;
	spec->hash = 0;
	spec->num = 0;
	spec->modif = 0;
	spec->znak = 0;
}

void			little_check(t_spesif *spec, char *format, int *i)
{
	if (spec->ac < 0 && spec->ac != -2)
		spec->ac = -1;
	(spec->ac == 0) ? spec->ac = -2 : 0;
	((format[(*i) - 1] == '.') && (format[*i] != '*') &&\
	(!ft_isdigit(format[*i]) || format[*i] == '0')) ? \
		(spec->ac = -2) : 0;
	if ((spec->width < 0) ? spec->width *= -1 : 0)
		spec->m = '-';
}

int				choose_sys(char b)
{
	if (b == 'u' || b == 'U')
		return (10);
	if (b == 'b')
		return (2);
	return ((b == 'o' || b == 'O') ? 8 : 16);
}

int				ft_checkstr(char *str, t_spesif *spec, int base)
{
	int i;
	int kost;

	i = -1;
	kost = 1;
	if (spec->hash && (spec->type == 'x' || spec->type == 'o'))
		spec->znak = ((spec->type == 'x') ? 0 : 1);
	if (spec->type == 'x' || spec->type == 'p')
		while (str[++i])
			str[i] = (char)ft_tolower(str[i]);
	else
		while (str[++i])
			;
	if (spec->ac == -2 && spec->num == 0)
		return (0);
	if (spec->hash && (spec->num != 0 || spec->type != 'p'))
		(base == 16) ? ++kost : 0;
	else
		kost--;
	if (spec->type == 'p' && spec->num == 0)
		return (3);
	return ((i >= spec->ac) ? (i + kost) : (spec->ac + kost));
}
