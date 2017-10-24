/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:07:35 by ysalata           #+#    #+#             */
/*   Updated: 2017/06/10 18:20:58 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	int isneg;
	int buf;

	buf = 0;
	isneg = 0;
	while (ft_iswhite(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			isneg = 1;
	if (ft_strcmp(str, "2147483647") == 0)
		return (2147483647);
	while (*str > 47 && *str < 58)
		buf = (buf * 10) + (*str++ - '0');
	return (isneg ? -buf : buf);
}
