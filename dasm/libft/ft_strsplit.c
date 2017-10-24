/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 14:41:30 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/07 13:57:43 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char			*ft_newword(char const *s, int start, int i)
{
	char	*startword;
	char	*word;

	if (!(word = ft_strnew(i - start + 1)))
		return (NULL);
	startword = word;
	while (i != start)
		*word++ = *(char *)(s + start++);
	*word = '\0';
	return (startword);
}

char				**ft_strsplit(char const *s, char c)
{
	int		i;
	int		wcount;
	int		start;
	char	**buf;
	char	**bstart;

	i = 0;
	if (!s)
		return (NULL);
	wcount = ft_countword(s, c);
	if (!(buf = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	bstart = buf;
	while (s[i] && wcount--)
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		*buf++ = ft_newword(s, start, i);
	}
	*buf = 0;
	return (bstart);
}
