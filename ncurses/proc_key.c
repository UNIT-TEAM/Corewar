/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:48:58 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 10:49:51 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		speed_change(t_ncurs *base, int a)
{
	if (base->n_cyc < 500 && a == 1)
	{
		base->n_cyc = base->n_cyc + 1;
		return (0);
	}
	if (base->n_cyc > 1 && a == 0)
	{
		base->n_cyc = base->n_cyc - 1;
		return (0);
	}
	if (base->n_cyc <= 490 && a == 2)
	{
		base->n_cyc = base->n_cyc + 10;
		return (0);
	}
	if (base->n_cyc >= 11 && a == -1)
	{
		base->n_cyc = base->n_cyc - 10;
		return (0);
	}
	return (0);
}

int		kb_proc(t_ncurs *base, int ch)
{
	if (ch == 32)
	{
		if (base->flag == 0)
			base->flag = 1;
		else
			base->flag = 0;
	}
	if (ch == 'e')
		speed_change(base, 1);
	if (ch == 'w')
		speed_change(base, 0);
	if (ch == 'r')
		speed_change(base, 2);
	if (ch == 'q')
		speed_change(base, -1);
	return (1);
}
