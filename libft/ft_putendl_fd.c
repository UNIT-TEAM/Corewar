/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:42:26 by tgogol            #+#    #+#             */
/*   Updated: 2016/11/28 14:15:03 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	int	i;

	i = -1;
	if (s != NULL)
	{
		while (s[++i])
			ft_putchar_fd(s[i], fd);
		write(fd, "\n", 1);
	}
}
