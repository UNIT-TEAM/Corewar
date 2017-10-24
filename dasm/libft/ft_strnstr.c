/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:07:01 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 15:28:33 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t l_len;

	l_len = ft_strlen((char *)little);
	if (l_len != 0)
		while (*big++ && len--)
			if ((ft_strncmp((big - 1), little, l_len) == 0) && \
				(len >= (l_len - 1)))
				return ((char *)(big - 1));
	return (l_len == 0 ? (char *)big : NULL);
}
