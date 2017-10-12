/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:32:35 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 23:12:44 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*buf;
	size_t			i;

	i = 0;
	if (!(buf = (void *)malloc(sizeof(buf) * size)))
		return (NULL);
	while (++i <= size)
		buf[i - 1] = 0;
	return (buf);
}
