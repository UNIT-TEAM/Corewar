/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 21:28:37 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 22:31:26 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (dst[i] && (i < size))
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	while (src[k] && (i < size - 1))
		dst[i++] = src[k++];
	dst[i] = '\0';
	return (i + ft_strlen(src) - k);
}
