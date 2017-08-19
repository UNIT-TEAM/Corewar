/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 19:18:04 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/14 19:18:10 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_wchar1(unsigned int n, int *r)
{
	unsigned int t;

	t = n >> 6;
	t = t | 192;
	write(1, &t, 1);
	t = n & 63;
	t = t | 128;
	write(1, &t, 1);
	*r += 2;
}

static void	print_wchar2(unsigned int n, int *r)
{
	unsigned int t;

	t = n >> 12;
	t = t | 224;
	write(1, &t, 1);
	t = n >> 6;
	t = t & 63;
	t = t | 128;
	write(1, &t, 1);
	t = n & 63;
	t = t | 128;
	write(1, &t, 1);
	*r += 3;
}

static void	print_wchar3(unsigned int n, int *r)
{
	unsigned int t;

	t = n >> 18;
	t = t | 240;
	write(1, &t, 1);
	t = n >> 12;
	t = t & 63;
	t = t | 128;
	write(1, &t, 1);
	t = n >> 6;
	t = t & 63;
	t = t | 128;
	write(1, &t, 1);
	t = n & 63;
	t = t | 128;
	write(1, &t, 1);
	*r += 4;
}

void		check_bit(int *nbr, int *r)
{
	unsigned int n;

	n = (unsigned int)(*nbr);
	if (n <= 255)
	{
		write(1, &n, 1);
		*r += 1;
	}
	else if (n > 127 && n <= 2047)
		print_wchar1(n, r);
	else if (n > 2047 && n <= 65535)
		print_wchar2(n, r);
	else if (n > 65535)
		print_wchar3(n, r);
}

void		print_upper_s(int *s, int *r, int size, int f)
{
	if (f)
		while (*s)
		{
			check_bit(s, r);
			s++;
		}
	else
		while (*s && size != *r)
		{
			check_bit(s, r);
			s++;
		}
}
