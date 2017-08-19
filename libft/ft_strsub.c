/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:55:48 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/04 21:15:26 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*buf;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((buf = ft_strnew(len)) == NULL)
		return (NULL);
	while (len--)
	{
		buf[i] = s[start + i];
		i++;
	}
	return (buf);
}
