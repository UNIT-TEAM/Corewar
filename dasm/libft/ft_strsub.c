/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:31:36 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 12:46:27 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *buf;
	char *bufstart;

	if (s == NULL)
		return (NULL);
	if (!(buf = ft_strnew(len)))
		return (NULL);
	bufstart = buf;
	while (len--)
		*buf++ = s[start++];
	*buf = '\0';
	return (bufstart);
}
