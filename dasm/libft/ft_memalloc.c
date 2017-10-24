/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:46:38 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 12:40:53 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char	*buf;
	char	*lol;

	if (!(buf = (char *)malloc(sizeof(buf) * size)))
		return (NULL);
	lol = buf;
	while (size--)
		*buf++ = 0;
	return (lol);
}
