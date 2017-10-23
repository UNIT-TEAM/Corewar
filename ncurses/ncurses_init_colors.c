/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_init_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:50:23 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 11:01:10 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		ncurses_init_colors(void)
{
	init_pair(1, 2, 0);
	init_pair(2, 4, 0);
	init_pair(3, 1, 0);
	init_pair(4, 6, 0);
	init_pair(5, 3, 0);
	init_pair(10, 82, 0);
	init_pair(20, 33, 0);
	init_pair(30, 9, 0);
	init_pair(40, 194, 0);
	init_pair(50, 11, 0);
	init_pair(101, 0, 2);
	init_pair(102, 0, 4);
	init_pair(103, 0, 1);
	init_pair(104, 0, 6);
	init_pair(105, 0, 3);
	init_pair(51, COLOR_WHITE, 2);
	init_pair(52, COLOR_WHITE, 4);
	init_pair(53, COLOR_WHITE, 1);
	init_pair(54, COLOR_WHITE, 6);
	init_pair(55, COLOR_WHITE, 3);
	init_pair(100, COLOR_BLACK, 8);
	init_pair(111, 8, 8);
	init_pair(112, 8, 0);
}
