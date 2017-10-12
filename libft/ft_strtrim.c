/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:27:55 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/04 21:17:12 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	c;
	size_t	q;
	char	*buf;

	i = 0;
	c = 0;
	q = 0;
	if (s == NULL)
		return (NULL);
	c = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (i - 1 == c)
	{
		if (!(buf = ft_strnew(0)))
			return (NULL);
		return (buf);
	}
	while (s[c] == ' ' || s[c] == '\n' || s[c] == '\t')
		c--;
	q = c - i + 1;
	if (!(buf = ft_strnew(q)))
		return (NULL);
	return (ft_strncpy(buf, &s[i], q));
}
