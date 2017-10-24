/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:08:40 by ysalata           #+#    #+#             */
/*   Updated: 2017/04/21 17:50:58 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ALL FUNCTIONS HERE TAKES THE INCREMENTING, USELESS FOR THEM, VALUE
** IT WAS DOING FOR LESS STRINGS IN CODE  ¯ \ _ (ツ) _ / ¯
*/

void				ft_write(char *a, int i)
{
	i += 0;
	write(1, a, 1);
}

/*
** Takes argument of CHAR * type
** Print string by (2)write while(howmuch)
*/

int					ft_swrite(char *a, t_format *tf, int howmuch)
{
	while (*a && howmuch--)
	{
		write(1, a++, 1);
		++(tf->retval);
	}
	return (1);
}

/*
** Takes argument of WCHAR_T *(LARGE CHAR *) type && INT len value
** Print by (2)write (in loop ny 6 bits) while(howmuch)
** !!!!!!!! NEED WORK !!!!!!!!
*/

void				ft_lswrite(int *value, t_format *tf, int howmuch, int coef)
{
	int			buf;

	buf = 0;
	if (howmuch <= 0 || !(*value))
		return ;
	if (*value <= 2048)
	{
		if ((coef = (*value >= 128) ? 1 : 0))
			buf = *value >> (coef * 6) | 192;
		else if (++(tf->retval))
			write(1, value, 1);
	}
	else if ((coef = (*value <= 65536) ? 2 : 3))
		buf = *value >> (coef * 6) | 224;
	else
		buf = *value >> (coef * 6) | 240;
	(coef > 0) ? (write(1, &buf, 1)) : 0;
	while (coef-- > 0)
	{
		buf = *value >> (coef * 6) & 63;
		buf |= 128;
		write(1, &buf, 1);
		++tf->retval;
	}
	ft_lswrite(++value, tf, --howmuch, 0);
}

/*
** Takes argument of CHAR * type && INT len value. Print by (2)write
*/

void				prf_putstr(char const *s, int *i)
{
	if (!s)
		return ;
	while (*s)
		ft_write(&*(char *)(s++), ++(*i));
}

/*
**	counts wchars
*/

size_t				ft_wstrlen(wchar_t *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
