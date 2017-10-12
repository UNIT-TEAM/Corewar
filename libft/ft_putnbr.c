/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 14:38:42 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 22:57:34 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int res;

	res = n;
	if (res < 0)
	{
		res *= (-1);
		ft_putchar('-');
	}
	if (res > 9)
	{
		ft_putnbr(res / 10);
	}
	ft_putchar(res % 10 + '0');
}
