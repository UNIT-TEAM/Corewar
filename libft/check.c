/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:05:07 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:07:16 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_type(char c)
{
	if (c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'o' || c == 'u'
		|| c == 'U' || c == 'X' || c == 'x' || c == 'c' || c == 'D' || c == 'O'
		|| c == 'b' || c == 'n' || c == 'C' || c == 'S')
		return (1);
	return (0);
}

int		check_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		check_flags(char c)
{
	if (c == ' ' || c == '-' || c == '+' || c == '#' || c == '0' || c == '.'
			|| c == '*')
		return (1);
	return (0);
}

int		check_minus_in_type(char c)
{
	if (c == '-')
		return (1);
	return (0);
}

int		isdigit_withoutziro(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}
