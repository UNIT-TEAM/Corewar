/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:41:03 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 11:13:51 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t l;

	l = ft_strlen(little);
	if (l == 0)
		return ((char *)big);
	len++;
	while (*big++ && len-- != 0 && l <= len)
		if (ft_strncmp(big - 1, little, l) == 0)
			return (char *)big - 1;
	return (NULL);
}
