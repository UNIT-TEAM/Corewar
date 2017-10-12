/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 19:41:34 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/14 19:41:46 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(t_prntf *bs, int fhesh, int fchar)
{
	int c;
	int f;

	f = 1;
	c = (int)ft_strlen(bs->str);
	if (c <= bs->nw)
	{
		c = bs->nw - c - fhesh + fchar;
		while (c-- > 0)
		{
			if (bs->spc && f && (bs->tp == 'd' || bs->tp == 'D' ||
				bs->tp == 'i'))
				f = 0;
			else
			{
				if (bs->z)
					print_aka_flags(1, '0', bs);
				else
					print_aka_flags(1, ' ', bs);
			}
		}
	}
}
