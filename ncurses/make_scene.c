/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 14:50:19 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 15:19:41 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "../corewar.h"

char const *g_base = "0123456789abcdef";

void			draw_cart(t_bs *bs)
{
	t_proc			*proc;
	unsigned int	a;
	char			y;

	proc = bs->list_proc;
	while (proc)
	{
		a = proc->pc;
		if (!bs->color_map[a].live)
		{
			if (bs->color_map[a].champ == 0)
				attron(COLOR_PAIR(100));
			else
				attron(COLOR_PAIR(bs->color_map[a].champ + 100));
			y = g_base[(bs->map[a] / 16) % 16];
			mvwprintw(stdscr, a / 64 + 2, (a % 64) * 3 + 2, "%c", y);
			y = g_base[bs->map[a] % 16];
			mvwprintw(stdscr, a / 64 + 2, (a % 64) * 3 + 1 + 2, "%c", y);
			if (bs->color_map[a].champ == 0)
				attroff(COLOR_PAIR(100));
			else
				attroff(COLOR_PAIR(bs->color_map[a].champ + 100));
		}
		proc = proc->next;
	}
}

int				find_color(t_bs *bs, int a)
{
	if (bs->color_map[a].champ == 0)
		return (112);
	if (g_count - bs->color_map[a].live <= 50 && bs->color_map[a].live != 0)
	{
		return (bs->color_map[a].champ + 50);
	}
	if (g_count - bs->color_map[a].cycle_n < 49 &&
			bs->color_map[a].cycle_n != 0)
	{
		return (bs->color_map[a].champ * 10);
	}
	return (bs->color_map[a].champ);
}

void			draw_mass(t_bs *bs, int a, int b)
{
	int x;
	int y;
	int color;

	x = 2;
	y = 2;
	while (b < 4096)
	{
		a = 0;
		while (a < 64)
		{
			color = find_color(bs, b);
			attron(COLOR_PAIR(color));
			mvwprintw(stdscr, y, x++, "%c", g_base[(bs->map[b] / 16) % 16]);
			mvwprintw(stdscr, y, x++, "%c", g_base[bs->map[b] % 16]);
			x++;
			attroff(COLOR_PAIR(color));
			a++;
			b++;
			bs->color_map[b].carretka = 0;
		}
		y++;
		x = 2;
	}
	draw_cart(bs);
}

void			create_box(WINDOW *p_win, int size)
{
	int x;
	int y;
	int h;
	int w;

	x = 0;
	y = 0;
	w = 265;
	h = 68;
	attron(COLOR_PAIR(111));
	mvwaddch(stdscr, y, x, '+');
	mvwaddch(stdscr, y, x + w, '+');
	mvwaddch(stdscr, y + h, x, '+');
	mvwaddch(stdscr, y + h, x + w, '+');
	mvwhline(stdscr, y, x + 1, '-', w - 1);
	mvwhline(stdscr, y + h, x + 1, '-', w - 1);
	mvwvline(stdscr, y + 1, x, '|', h - 1);
	mvwvline(stdscr, y + 1, x + w, '|', h - 1);
	mvwvline(stdscr, y + 1, x + 200, '|', h - 1);
	attroff(COLOR_PAIR(111));
	refresh();
	wrefresh(p_win);
}

void			ncurses_init_win(t_ncurs *base)
{
	initscr();
	cbreak();
	start_color();
	ncurses_init_colors();
	noecho();
	base->n_cyc = 50;
	base->flag = 0;
	base->window = stdscr;
}
