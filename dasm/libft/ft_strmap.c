/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:54:14 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 12:36:40 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char *buf;
	char *d;

	if (s == NULL || !(buf = ft_strnew(ft_strlen(s))))
		return (NULL);
	d = buf;
	while (*s)
		*buf++ = f(*s++);
	*buf = '\0';
	return (d);
}
