/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woodman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:47:20 by ysalata           #+#    #+#             */
/*   Updated: 2017/04/21 17:04:26 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Little tip for u:
** 1 - hh | 2 - h | 3 - l | 4 - L | 5 - ll | 6 - j | 7 - z
** WOODMAN CASTING IS BEST CAST I'VE EVER SEEN
** Hope u likes it 2. ;)
*/

unsigned long long int		tsize_uns(int i, va_list ap)
{
	if (i < 0)
		return (0);
	if (i == 0)
		return (va_arg(ap, unsigned int));
	if (i > 4)
	{
		if (i == 5)
			return (va_arg(ap, unsigned long long int));
		if (i == 6)
			return (va_arg(ap, uintmax_t));
		return (va_arg(ap, size_t));
	}
	if (i < 3)
		return ((i == 1) ? (unsigned char)va_arg(ap, unsigned long long int) \
				: (unsigned short)va_arg(ap, unsigned long long int));
	else if (i == 3)
		return (va_arg(ap, unsigned long));
	return (va_arg(ap, unsigned long long int));
}

long long int				tsize_dec(int i, va_list ap)
{
	if (i < 0)
		return (0);
	if (i == 0)
		return (va_arg(ap, int));
	else if (i > 4)
		return ((i == 5) ? va_arg(ap, long long int) : va_arg(ap, intmax_t));
	else if (i < 3)
		return ((i == 1) ? (signed char)va_arg(ap, long long int)\
				: (short)va_arg(ap, long long int));
	else if (i == 3)
		return (va_arg(ap, long int));
	return (va_arg(ap, long long int));
}

long long int				*tsize_n(int i, va_list ap)
{
	if (i < 0)
		return (0);
	else if (i == 0)
		return ((long long int *)va_arg(ap, int *));
	else if (i > 4)
		return ((i == 5) ? va_arg(ap, long long int *) \
				: (long long int *)va_arg(ap, intmax_t *));
	else if (i < 3)
		return ((i == 1) ? (long long int *)va_arg(ap, signed char *) \
				: (long long int *)va_arg(ap, short *));
	else
		return ((i == 3) ? (long long int *)va_arg(ap, long int *) :\
		va_arg(ap, long long int*));
}
