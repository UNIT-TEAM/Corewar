/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 20:48:23 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 12:43:58 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *buf;

	buf = dst;
	while (len--)
		if (*src != '\0')
			*dst++ = *src++;
		else
			*dst++ = '\0';
	return (buf);
}
