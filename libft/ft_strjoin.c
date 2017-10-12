/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:15:58 by tgogol            #+#    #+#             */
/*   Updated: 2016/12/01 23:15:03 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *buf;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(buf = ft_strnew((ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	buf = ft_strcpy((char *)buf, s1);
	return (buf = ft_strcat(buf, s2));
}
