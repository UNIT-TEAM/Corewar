/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_n_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:18:00 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:18:03 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_modificator(char *s, char *mdf)
{
	while ((*s) && (check_flags(*s) || ft_isdigit(*s) || *s == '.' ||
					check_length(*s) || check_length(*s)))
	{
		if (*s == 'h')
		{
			if (*mdf == 'h')
				*mdf = 'H';
			else if (*mdf != 'l' && *mdf != 'L' && *mdf != 'z' && *mdf != 'j')
				*mdf = 'h';
		}
		if (*s == 'l')
		{
			if (*mdf == 'l')
				*mdf = 'L';
			else if (*mdf != 'z' || *mdf != 'j')
				*mdf = 'l';
		}
		if (*s == 'z')
			*mdf = (*mdf != 'j') ? 'z' : 'j';
		(*s == 'j') ? *mdf = 'j' : 0;
		s++;
	}
}

void	fill_priority(t_prntf **bs)
{
	if ((*bs)->z && (*bs)->m)
		(*bs)->z = 0;
	if ((*bs)->spc && (*bs)->pls)
		(*bs)->spc = 0;
	if ((*bs)->prc >= 0 && ((*bs)->tp == 'd' || (*bs)->tp == 'D' ||
		(*bs)->tp == 'x' || (*bs)->tp == 'X' ||
		(*bs)->tp == 'i' || (*bs)->tp == 'o' ||
		(*bs)->tp == 'O' || (*bs)->tp == 'u' ||
		(*bs)->tp == 'U' || (*bs)->tp == 'b'))
		(*bs)->z = 0;
}

void	fill_bitoa(char c, int *bitoa)
{
	if (c == 'u' || c == 'U')
		*bitoa = 10;
	else if (c == 'x' || c == 'X')
		*bitoa = 16;
	else if (c == 'o' || c == 'O')
		*bitoa = 8;
	else if (c == 'b')
		*bitoa = 2;
}

void	fill_type(char *s, char *tp)
{
	while (*s && (check_afte_pers(*s) || ft_isdigit(*s)))
		s++;
	if (check_type(*s))
		*tp = *s;
}

int		check_afte_pers(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == ' ' || c == '.'
		|| c == '+' || c == '-' || c == '#' || c == '*')
		return (1);
	return (0);
}
