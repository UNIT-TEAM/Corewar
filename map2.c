/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:54:20 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 20:06:09 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_cycle_to_die(t_bs *bs, long *cycle_to_die,
					unsigned int *max_check,
					unsigned int *cycle_to_die_curr)
{
	t_chmp	*tmp_champ;
	t_proc	*tmp;

	tmp_champ = bs->list_champs;
	if (*cycle_to_die_curr == *cycle_to_die)
	{
		while (tmp_champ)
		{
			tmp_champ->live = 0;
			tmp_champ = tmp_champ->next;
		}
		if (check_is_live(&bs->list_proc, bs->is_beep, tmp) == 0)
			return (0);
		if (bs->num_live >= NBR_LIVE || *max_check == 1)
		{
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else
			--(*max_check);
		*cycle_to_die_curr = 0;
		bs->num_live = 0;
	}
	return (1);
}

void		who_win(t_chmp *champ, unsigned int *winner)
{
	t_chmp			*tmp;
	unsigned int	max_cycle;

	tmp = champ;
	*winner = tmp->num;
	max_cycle = tmp->cycle_live;
	tmp = tmp->next;
	while (tmp)
	{
		if (max_cycle < tmp->cycle_live)
		{
			*winner = tmp->num;
			max_cycle = tmp->cycle_live;
		}
		else if (max_cycle == tmp->cycle_live)
			*winner = (tmp->num > *winner) ? tmp->num : *winner;
		tmp = tmp->next;
	}
}

void		set_chmps_with_flag_num(t_bs *bs)
{
	t_chmp	*tmp_chmp;
	t_proc	*tmp_proc;
	int		k;

	tmp_chmp = bs->list_champs;
	tmp_proc = bs->list_proc;
	while (tmp_chmp)
	{
		if (tmp_chmp->flag_num != 0)
		{
			tmp_chmp->num = tmp_chmp->flag_num;
			tmp_proc->regs[0] = (unsigned int)(-tmp_chmp->num);
			tmp_proc->id = tmp_chmp->num;
			tmp_proc->pc = (tmp_chmp->flag_num - 1) * (MEM_SIZE / bs->np);
			k = -1;
			while (++k < tmp_chmp->head.prog_size)
			{
				bs->map[tmp_proc->pc + k] = tmp_chmp->instructions[k];
				add_color(tmp_proc->pc + k, tmp_chmp->num, bs);
			}
		}
		tmp_chmp = tmp_chmp->next;
		tmp_proc = tmp_proc->next;
	}
}

void		set_chmps_without_flag_num(t_bs *bs, unsigned int i, int k,
			t_proc *tmp_proc)
{
	t_chmp			*tmp_chmp;

	tmp_chmp = bs->list_champs;
	tmp_proc = bs->list_proc;
	while (tmp_chmp)
	{
		if (tmp_chmp->flag_num == 0)
		{
			while (bs->map[i] != 0x0)
				i += MEM_SIZE / bs->np;
			tmp_proc->pc = i;
			tmp_chmp->num = i / (MEM_SIZE / bs->np) + 1;
			tmp_proc->regs[0] = (unsigned int)(-tmp_chmp->num);
			tmp_proc->id = tmp_chmp->num;
			k = -1;
			while (++k < tmp_chmp->head.prog_size)
			{
				bs->map[tmp_proc->pc + k] = tmp_chmp->instructions[k];
				add_color(tmp_proc->pc + k, tmp_chmp->num, bs);
			}
			i += MEM_SIZE / bs->np;
		}
		tmp_chmp = tmp_chmp->next;
		tmp_proc = tmp_proc->next;
	}
}

void		g_c_prep(t_ncurs *ncurs, t_bs *bs)
{
	if (ncurs->ch == 0)
	{
		++g_count;
		draw_mass(bs, 0, 0);
		who_win(bs->list_champs, &bs->winner);
		ncurses_stats(ncurs->window, ncurs, bs, 0);
		ncurses_result(ncurs, bs);
		while (getch() < 0)
		{
		}
	}
	endwin();
}
