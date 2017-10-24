/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:42:11 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 11:27:38 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*dup;
	char	*buf;

	if (!(dup = (char *)malloc(sizeof(*dup) * (ft_strlen(str) + 1))))
		return (NULL);
	buf = dup;
	while (*str)
		*dup++ = *(char *)str++;
	*dup = '\0';
	return (buf);
}
