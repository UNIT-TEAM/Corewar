/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:04:25 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 23:18:40 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*buf;
	int		i;

	i = -1;
	if (s == NULL)
		return (NULL);
	if (!(buf = (char*)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[++i])
		buf[i] = f(s[i]);
	buf[i] = '\0';
	return (buf);
}
