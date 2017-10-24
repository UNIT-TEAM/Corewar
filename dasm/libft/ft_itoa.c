/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:19:44 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/07 12:59:40 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_wordnum(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char			*buf;
	unsigned int	x;
	int				i;
	int				wordnum;

	i = 0;
	wordnum = ft_wordnum(n);
	if (!(buf = ft_strnew(wordnum)))
		return (NULL);
	x = n;
	if (n < 0)
		x = -n;
	if (x == 0)
		buf[i++] = '0';
	while (x > 0)
	{
		buf[i++] = x % 10 + '0';
		x /= 10;
	}
	if (n < 0)
		buf[i++] = '-';
	buf[i] = '\0';
	ft_strrev(buf);
	return (buf);
}
