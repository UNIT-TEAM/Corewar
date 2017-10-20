#include "corewar.h"

void	print_map(unsigned char *map)
{
	int i;
	int j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			ft_printf("%02x", *map);
			(j != 64 - 1) ? ft_printf(" ") : 0;
			++map;
			++j;
		}
		ft_printf("\n");
		++i;
	}
	ft_printf("\n");
}


void    check_inst_proc(t_bs *bs, t_proc **procs, unsigned char *map, t_chmp *champs)
{
    t_proc *tmp;

    tmp = *procs;
    while (tmp)
    {
		if (map[tmp->pc] == op_tab[0].opcode)
			ft_live(map, tmp, 0, champs);
		else if (map[tmp->pc] == op_tab[1].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 1);
		else if (map[tmp->pc] == op_tab[2].opcode)
			ft_st_sti(bs, tmp, 2);
		else if (map[tmp->pc] == op_tab[3].opcode)
			ft_add_sub_and_or_xor(map, tmp, 3);
		else if (map[tmp->pc] == op_tab[4].opcode)
			ft_add_sub_and_or_xor(map, tmp, 4);
		else if (map[tmp->pc] == op_tab[5].opcode)
			ft_add_sub_and_or_xor(map, tmp, 5);
		else if (map[tmp->pc] == op_tab[6].opcode)
			ft_add_sub_and_or_xor(map, tmp, 6);
		else if (map[tmp->pc] == op_tab[7].opcode)
			ft_add_sub_and_or_xor(map, tmp, 7);
		else if (map[tmp->pc] == op_tab[8].opcode)
			ft_zjump(map, tmp, 8);
		else if (map[tmp->pc] == op_tab[9].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 9);
		else if (map[tmp->pc] == op_tab[10].opcode)
			ft_st_sti(bs, tmp, 10);
		else if (map[tmp->pc] == op_tab[11].opcode)
			ft_fork_lfork(map, procs, tmp, 11);
		else if (map[tmp->pc] == op_tab[12].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 12);
		else if (map[tmp->pc] == op_tab[13].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 13);
		else if (map[tmp->pc] == op_tab[14].opcode)
			ft_fork_lfork(map, procs, tmp, 14);
		else if (map[tmp->pc] == op_tab[15].opcode)
			ft_aff(map, tmp, 15);
		else
			tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		tmp = tmp->next;
    }
}

int		check_is_live(t_proc **procs)
{
	t_proc *tmp;
	t_proc *prev;

	tmp = *procs;
	prev = tmp;
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		if (tmp->is_live)
		{
			tmp->is_live = 0;
			prev = tmp;
		}
		else
		{
			if (*procs == tmp)
				*procs = tmp->next;
			prev->next = tmp->next;
			free(tmp);
		}
		tmp = prev->next;
	}
	if (*procs == NULL)
		return (0);
	return (1);
}

int		check_cycle_to_die(t_bs *bs, long *cycle_to_die,
						unsigned int *max_check,
						unsigned int *cycle_to_die_curr)
{
	t_chmp			*tmp;
	unsigned int	nbr_live;

	if (*cycle_to_die_curr == *cycle_to_die)
	{
		nbr_live = 0;
		tmp = bs->list_champs;
		while (tmp)
		{
			if (tmp->live != 0)
			{
				nbr_live += tmp->live;
				tmp->live = 0;
			}
			tmp = tmp->next;
		}
		if (check_is_live(&bs->list_proc) == 0)
			return (0);
		if (nbr_live >= NBR_LIVE || *max_check == 0)
		{
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else
			--(*max_check);
		*cycle_to_die_curr = 0;
	}
	return (1);
}

void	who_win(t_chmp *champ, unsigned int *winner)
{
	t_chmp *tmp;
	unsigned int max_cycle;

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

void	set_chmps_with_flag_num(t_bs *bs)
{
	t_chmp *tmp_chmp;
	t_proc *tmp_proc;
	int k;

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
	//print_map(bs->map);
}

void	set_chmps_without_flag_num(t_bs *bs)
{
	unsigned int i;
	int k;
	t_chmp *tmp_chmp;
	t_proc *tmp_proc;

	i = 0;
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
	//print_map(bs->map);
}

void	global_cycles(t_bs *bs)
{
	long cycle_to_die;
	unsigned int cycle_to_die_curr;
	unsigned int max_check;
	int ch;

	cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die_curr = 0;
	max_check = MAX_CHECKS;

	t_ncurs *ncurs = malloc(sizeof(t_ncurs));
	ncurses_init_win(ncurs);
	nodelay(stdscr,TRUE);
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
		draw_mass(bs, 4096);
		ncurses_stats(ncurs->window, ncurs,bs);

		if (ncurs->flag || ch == 'n') {
			++g_count;
			++cycle_to_die_curr;
			check_inst_proc(bs, &bs->list_proc, bs->map, bs->list_champs);
			if (bs->is_dump && bs->dump == g_count)
			{
				print_map(bs->map);
				break;
			}
			if (bs->is_print && bs->cycle_print % g_count == 0)
				print_map(bs->map);
			if (check_cycle_to_die(bs, &cycle_to_die, &max_check,
								   &cycle_to_die_curr) == 0)
				break;
		}
		ch = 0;
	}
	endwin();
	who_win(bs->list_champs, &bs->winner);
}

void	global_cycles2(t_bs *bs)
{
	long cycle_to_die;
	unsigned int cycle_to_die_curr;
	unsigned int max_check;

	cycle_to_die = CYCLE_TO_DIE;
	cycle_to_die_curr = 0;
	max_check = MAX_CHECKS;

	while (cycle_to_die > 0)
	{
		++cycle_to_die_curr;
		check_inst_proc(bs, &bs->list_proc, bs->map, bs->list_champs);
		if (bs->is_dump && bs->dump == g_count) {
			// print_map(bs->map);
			break;
		}
//		if (bs->is_dump_go && bs->dump_go % g_count == 0)
//			// print_map(bs->map);
		if (check_cycle_to_die(bs, &cycle_to_die, &max_check,
							   &cycle_to_die_curr) == 0)
			break;
	}

	who_win(bs->list_champs, &bs->winner);
}

void	ft_fill_map(t_bs *bs)
{
	if (bs->is_num_flag)
		set_chmps_with_flag_num(bs);
	set_chmps_without_flag_num(bs);
	//print_map(bs->map);
	if (bs->is_visual)
		global_cycles(bs);
	else
		global_cycles2(bs);
}