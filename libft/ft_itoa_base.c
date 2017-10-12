/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:21:05 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:21:08 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_pf(uintmax_t n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_itoab_u(long unsigned int value, int base, char c)
{
	char		*s;
	uintmax_t	nb;
	int			i;

	i = count_pf(value, base);
	if (value == 0)
		return ("0");
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i] = '\0';
	while (value != 0)
	{
		nb = value % base;
		(nb > 9 && base > 9 && c == 'X') ? nb = nb + 7 : 0;
		(nb > 9 && base > 9 && c == 'x') ? nb = nb + 39 : 0;
		s[i - 1] = nb + '0';
		value /= base;
		i--;
	}
	return (s);
}

int		count(intmax_t n, int base)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0 && base == 10)
		i++;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa_b(intmax_t value, int base)
{
	char		*s;
	intmax_t	nb;
	int			i;

	i = count(value, base);
	if (value == 0)
		return ("0");
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i] = '\0';
	if (value < 0)
		s[0] = '-';
	while (value != 0)
	{
		nb = value % base;
		if (nb < 0)
			nb = -nb;
		if (nb > 9 && base > 9)
			nb = nb + 7;
		s[i - 1] = nb + '0';
		value /= base;
		i--;
	}
	return (s);
}
