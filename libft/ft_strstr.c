/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:04:45 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 11:02:39 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t l;

	l = ft_strlen(little);
	if (l == 0)
		return ((char *)big);
	while (*(big++))
		if (ft_strncmp(big - 1, little, l) == 0)
			return (char *)big - 1;
	return (NULL);
}
