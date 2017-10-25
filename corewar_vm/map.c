/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:50:26 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 20:07:46 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	g_c_with_v(t_bs *bs, long c_to_d, unsigned int max_check,
		t_ncurs *ncurs)
{
	while (c_to_d > 0)
	{
		ncurs->cyc_to_die = c_to_d;
		create_box(ncurs->window, 1);
		ncurs->ch = getch();
		if (kb_proc(ncurs, ncurs->ch) && ncurs->ch == 27)
			break ;
		if (ncurs->ch != 's')
			usleep(1000000 / ncurs->n_cyc);
		ncurses_stats(ncurs->window, ncurs, bs, 1);
		if (g_count == 0)
			draw_mass(bs, 0, 0);
		if (ncurs->flag || ncurs->ch == 's')
		{
			++g_count;
			++(ncurs->cy);
			ncurs->ch = 0;
			check_inst_proc(bs, &bs->list_proc, bs->map, bs->list_champs);
			if (check_cycle_to_die(bs, &c_to_d, &max_check, &(ncurs->cy)) == 0)
				break ;
		}
		draw_mass(bs, 0, 0);
		ncurs->ch = 0;
	}
	g_c_prep(ncurs, bs);
}

void	global_cycles_without_visual(t_bs *bs)
{
	long			cycle_to_die;
	unsigned int	cycle_to_die_curr;
	unsigned int	max_check;

	cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die_curr = 0;
	max_check = MAX_CHECKS;
	while (cycle_to_die > 0)
	{
		++g_count;
		++cycle_to_die_curr;
		check_inst_proc(bs, &bs->list_proc, bs->map, bs->list_champs);
		if (bs->is_dump && bs->dump == g_count)
		{
			print_map(bs->map);
			break ;
		}
		if (bs->is_print && g_count % bs->cycle_print == 0)
			print_map(bs->map);
		if (check_cycle_to_die(bs, &cycle_to_die, &max_check,
				&cycle_to_die_curr) == 0)
			break ;
	}
	++g_count;
	who_win(bs->list_champs, &bs->winner);
}

void	reverse_champs(t_chmp **champs)
{
	t_chmp *prev;
	t_chmp *curr;
	t_chmp *next;

	prev = NULL;
	curr = *champs;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*champs = prev;
}

void	ft_fill_map(t_bs *bs)
{
	t_ncurs	*ncurs;
	t_proc	*tmp_proc;

	ncurs = NULL;
	if (bs->is_visual)
		ncurs = malloc(sizeof(t_ncurs));
	if (bs->is_num_flag)
		set_chmps_with_flag_num(bs);
	set_chmps_without_flag_num(bs, 0, 0, tmp_proc);
	print_champs(bs->list_champs, bs->is_visual);
	if (bs->is_visual)
	{
		ncurs->cy = 0;
		ncurses_init_win(ncurs);
		nodelay(stdscr, TRUE);
		g_c_with_v(bs, CYCLE_TO_DIE, MAX_CHECKS, ncurs);
	}
	else
		global_cycles_without_visual(bs);
	if (bs->is_visual && ncurs != NULL)
		free(ncurs);
}
