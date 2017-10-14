#include "corewar.h"
//
//void	print_map(unsigned char *map)
//{
//	int i;
//	int j;
//
//	i = 0;
//	while (i < 64)
//	{
//		j = 0;
//		while (j < 64)
//		{
//			ft_printf("%02x", *map);
//			(j != 64 - 1) ? ft_printf(" ") : 0;
//			++map;
//			++j;
//		}
//		ft_printf("\n");
//		++i;
//	}
//	ft_printf("\n");
//}

void    check_inst_proc(t_proc **procs, t_bs *base, t_chmp *champs)
{
    t_proc *tmp;
	t_proc *prev;

    tmp = *procs;
	prev = tmp;
    while (tmp)
    {
    	if (tmp->is_live)
		{
			if (base->map[tmp->pc] == op_tab[0].opcode)
				ft_live(base, tmp, 0, champs);
			else if (base->map[tmp->pc] == op_tab[1].opcode)
				ft_ld_lld(base, tmp, 1, 0);
			else if (base->map[tmp->pc] == op_tab[2].opcode)
				ft_st_sti(base, tmp, 2, 0);
			else if (base->map[tmp->pc] == op_tab[3].opcode)
				ft_add_sub(base, tmp, 3, 0);
			else if (base->map[tmp->pc] == op_tab[4].opcode)
				ft_add_sub(base, tmp, 4, 1);
			else if (base->map[tmp->pc] == op_tab[5].opcode)
				ft_and_or_xor(base, tmp, 5, 0);
			else if (base->map[tmp->pc] == op_tab[6].opcode)
				ft_and_or_xor(base, tmp, 6, 1);
			else if (base->map[tmp->pc] == op_tab[7].opcode)
				ft_and_or_xor(base, tmp, 7, 2);
			else if (base->map[tmp->pc] == op_tab[8].opcode)
				ft_zjump(base, tmp, 8);
			else if (base->map[tmp->pc] == op_tab[9].opcode)
				ft_ldi_lldi(base, tmp, 9, 0);
			else if (base->map[tmp->pc] == op_tab[10].opcode)
				ft_st_sti(base, tmp, 10, 1);
			else if (base->map[tmp->pc] == op_tab[11].opcode)
				ft_fork(base, procs, tmp, 11);
			else if (base->map[tmp->pc] == op_tab[12].opcode)
				ft_ld_lld(base, tmp, 12, 1);
			else if (base->map[tmp->pc] == op_tab[13].opcode)
				ft_ldi_lldi(base, tmp, 13, 1);
			else if (base->map[tmp->pc] == op_tab[14].opcode)
				ft_lfork(base, procs, tmp, 14);
			else if (base->map[tmp->pc] == op_tab[15].opcode)
				ft_aff(base, tmp, 15);
			else
				tmp->pc = (tmp->pc + 1) % MEM_SIZE;
			++tmp->cycle_to_die;
			prev = tmp;
			tmp = tmp->next;
		}
		else
		{
			if (*procs == tmp)
				*procs = tmp->next;
			prev->next = tmp->next;
			free(tmp);
			tmp = prev->next;
		}
    }
}

void check_cycle_to_die(t_chmp *players, long *cycle_to_die,
						unsigned int *max_check,
						unsigned int *cycle_to_die_curr)
{
	t_chmp			*tmp;
	unsigned int	nbr_live;

	nbr_live = 0;
	tmp = players;
	while (tmp)
	{
		if (tmp->live != 0)
			nbr_live += tmp->live;
		tmp = tmp->next;
	}
	if (*cycle_to_die_curr == *cycle_to_die)
	{
		if (nbr_live >= NBR_LIVE || *max_check)
		{
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else if (nbr_live)
			(*max_check)--;

		*cycle_to_die_curr = 0;
	}
}

void	check_is_live_in_proc(t_proc *proc, long cycle_to_die)
{
	t_proc *tmp;

	tmp = proc;
	while (tmp)
	{
		if (tmp->cycle_to_die == cycle_to_die)
			tmp->is_live = 0;
		tmp = tmp->next;
	}
}
void	global_cycles(t_bs *bs)
{
	long cycle_to_die;
	unsigned int cycle_to_die_curr;
	unsigned int max_check;

	cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die_curr = 0;
	max_check = MAX_CHECKS;

    t_ncurs *ncurs = malloc(sizeof(t_ncurs));
    ncurses_init_win(ncurs);
    nodelay(stdscr,TRUE);
    int ch;

	while (cycle_to_die > 0)
	{
        create_box(ncurs->window, 1);
        ch = getch();
        if (kb_proc(ncurs,ch) && ch == 27)
        {
            break;
        }
        if (ch != 'n')
            usleep(1000000/ncurs->n_cyc);
        draw_mass(bs, 0, 0);
        ncurses_stats(ncurs->window, ncurs,bs);
        if (ncurs->flag|| ch == 'n') {
           ++g_count;
            ++cycle_to_die_curr;
            check_inst_proc(&bs->list_proc, bs, bs->list_champs);
            if (bs->is_dump && bs->dump == g_count) {
                break;
            }
            if (bs->is_dump_go && bs->dump_go % g_count == 0)
                 check_cycle_to_die(bs->list_champs, &cycle_to_die, &max_check, &cycle_to_die_curr);
            check_is_live_in_proc(bs->list_proc, cycle_to_die);
        }
        ch = 0;
	}
    endwin();
}

void	ft_fill_map(t_bs *bs)
{
	int 			i;
	unsigned int	pftr;
	int 			k;
	t_chmp			*tmp;
	t_proc          *tp;

	i = -1;
	pftr = 0;
	tmp = bs->list_champs;
	tp = bs->list_proc;
	while (++i < bs->np)
	{
		pftr = (i == 0) ? 0 : pftr + MEM_SIZE / bs->np;
		tp->pc = pftr;
		k = -1;
		while (++k < tmp->head.prog_size)
		{
			bs->map[pftr + k] = tmp->instructions[k];
			add_color(pftr + k, tmp->num, bs);
//			bs->color_map[pftr +k].champ = (char) tmp->num;
//			bs->color_map[pftr +k].cycle_n = g_count;
		}
		tp = tp->next;
		tmp = tmp->next;
	}
	global_cycles(bs);
}