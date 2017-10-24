/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:19:39 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 12:41:41 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*buf;
	unsigned int	i;

	if (s == NULL || !(buf = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = -1;
	while (s[++i])
		buf[i] = f(i, s[i]);
	buf[i] = '\0';
	return (buf);
}
