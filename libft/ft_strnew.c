/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:06:49 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/04 21:13:50 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_strnew(size_t size)
{
	char	*b;
	size_t	i;

	i = 0;
	if (!(b = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
		b[i++] = '\0';
	b[i++] = '\0';
	return (b);
}
