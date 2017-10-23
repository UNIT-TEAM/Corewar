/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 14:20:20 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 14:46:02 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int			proc_count(t_bs *bs)
{
	t_proc	*proc;
	int		a;

	proc = bs->list_proc;
	a = 0;
	while (proc)
	{
		a++;
		proc = proc->next;
	}
	return (a);
}

void		ncurses_result(t_ncurs *base, t_bs *bs)
{
	t_chmp	*chmp;
	char	*name;
	int		col;

	chmp = bs->list_champs;
	while (chmp)
	{
		if (chmp->num == bs->winner)
		{
			name = chmp->head.prog_name;
			col = chmp->num;
		}
		chmp = chmp->next;
	}
	base->b += 2;
	mvwprintw(base->window, base->b, base->a, "The winner is : ");
	attron(COLOR_PAIR(col));
	mvwprintw(base->window, base->b, base->a + 19, "%s", name);
	base->b += 2;
	attroff(COLOR_PAIR(col));
	mvwprintw(base->window, base->b, base->a, "Press any key to finish");
}

void		ncurses_stats2(WINDOW *w, t_ncurs *base, t_bs *bs, int a)
{
	t_chmp	*chmps;

	chmps = bs->list_champs;
	while (chmps)
	{
		mvwprintw(w, base->b, base->a, "Player -%d :", chmps->num);
		attron(COLOR_PAIR(chmps->num));
		mvwprintw(w, base->b++, base->a + 15, "%s", chmps->head.prog_name);
		attroff(COLOR_PAIR(chmps->num));
		mvwprintw(w, base->b++, base->a, "Last live :              %d",
				chmps->cycle_live);
		mvwprintw(w, base->b++, base->a, "Lives in curent period : %d        ",
				chmps->live);
		base->b++;
		chmps = chmps->next;
	}
	if (a == 0)
		mvwprintw(w, base->b++, base->a, "CYCLES TO DIE : %d   ", 0);
	mvwprintw(w, base->b++, base->a, "CYCLES TO DIE : %d   ", base->cyc_to_die);
	base->b++;
	mvwprintw(w, base->b++, base->a, "CYCLE_DELTA : %d   ", CYCLE_DELTA);
	base->b++;
	mvwprintw(w, base->b++, base->a, "NBR_LIVE : %d   ", NBR_LIVE);
	base->b++;
	mvwprintw(w, base->b++, base->a, "MAX_CHECKS : %d   ", MAX_CHECKS);
}

void		ncurses_stats(WINDOW *w, t_ncurs *base, t_bs *bs, int a)
{
	t_chmp	*chmps;

	base->a = 206;
	base->b = 2;
	chmps = bs->list_champs;
	if (!base->flag)
		mvwprintw(w, base->b++, base->a, "%s", "** PAUSED **");
	else
		mvwprintw(w, base->b++, base->a, "%s", "** RUNING **");
	mvwprintw(w, base->b, base->a, "%s", "Cycles/second limit :");
	mvwprintw(w, base->b++, base->a + 25, "%d     ", base->n_cyc);
	base->b += 2;
	mvwprintw(w, base->b, base->a, "%s", "Cycle :");
	mvwprintw(w, base->b++, base->a + 10, "%d", g_count);
	base->b++;
	mvwprintw(w, base->b, base->a, "%s", "Processes :");
	mvwprintw(w, base->b++, base->a + 15, "%d    ", proc_count(bs));
	base->b++;
	ncurses_stats2(w, base, bs, a);
}
