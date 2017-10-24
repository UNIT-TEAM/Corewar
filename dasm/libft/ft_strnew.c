/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:10:49 by ysalata           #+#    #+#             */
/*   Updated: 2017/03/20 16:27:18 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strnew(size_t size)
{
	char *buf;
	char *lol;

	if (!(buf = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	lol = buf;
	size++;
	while (size--)
		*buf++ = '\0';
	return (lol);
}
