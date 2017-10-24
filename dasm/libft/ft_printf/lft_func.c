/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lft_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:59:25 by ysalata           #+#    #+#             */
/*   Updated: 2017/05/22 18:48:53 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	HERE IS COPY OF STANDART LIBFT FUNCTIONS :
**	ft_tolower | ft_strlen | ft_isdigit | ft_strchr
*/

/*
** V for vendetta, K for kostul'
*/

char		*ft_kstrchr(const char *s, int c)
{
	char *k;

	k = "K";
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (!*s)
			break ;
		s++;
	}
	return (k);
}
