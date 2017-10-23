/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddovzhik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 23:52:55 by ddovzhik          #+#    #+#             */
/*   Updated: 2017/10/23 23:52:56 by ddovzhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_color(int a, unsigned int champ, t_bs *bs)
{
	bs->color_map[a].champ = (char)champ;
	bs->color_map[a].cycle_n = g_count;
}
