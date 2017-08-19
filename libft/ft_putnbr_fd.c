/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:51:21 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 23:02:11 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int res;

	res = n;
	if (res < 0)
	{
		res *= (-1);
		ft_putchar_fd('-', fd);
	}
	if (res > 9)
	{
		ft_putnbr_fd((res / 10), fd);
	}
	ft_putchar_fd((res % 10 + '0'), fd);
}
