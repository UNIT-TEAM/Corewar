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
		if (tmp->inst_cycle == 0)
			tmp->opcode = map[tmp->pc];
		if (tmp->opcode == op_tab[0].opcode)
			ft_live(bs, tmp, 0, champs);
		else if (tmp->opcode == op_tab[1].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 1);
		else if (tmp->opcode == op_tab[2].opcode)
			ft_st_sti(bs, tmp, 2);
		else if (tmp->opcode == op_tab[3].opcode)
			ft_add_sub_and_or_xor(map, tmp, 3);
		else if (tmp->opcode == op_tab[4].opcode)
			ft_add_sub_and_or_xor(map, tmp, 4);
		else if (tmp->opcode == op_tab[5].opcode)
			ft_add_sub_and_or_xor(map, tmp, 5);
		else if (tmp->opcode == op_tab[6].opcode)
			ft_add_sub_and_or_xor(map, tmp, 6);
		else if (tmp->opcode == op_tab[7].opcode)
			ft_add_sub_and_or_xor(map, tmp, 7);
		else if (tmp->opcode == op_tab[8].opcode)
			ft_zjump(map, tmp, 8);
		else if (tmp->opcode == op_tab[9].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 9);
		else if (tmp->opcode == op_tab[10].opcode)
			ft_st_sti(bs, tmp, 10);
		else if (tmp->opcode == op_tab[11].opcode)
			ft_fork_lfork(map, procs, tmp, 11);
		else if (tmp->opcode == op_tab[12].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 12);
		else if (tmp->opcode == op_tab[13].opcode)
			ft_ld_lld_ldi_lldi(map, tmp, 13);
		else if (tmp->opcode == op_tab[14].opcode)
			ft_fork_lfork(map, procs, tmp, 14);
		else if (tmp->opcode == op_tab[15].opcode)
			ft_aff(map, tmp, 15, bs->is_aff);
		else
			tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		tmp = tmp->next;
    }
}

int	get_len_procs(t_proc *procs)
{
	int i = 0;

	while (procs)
	{
		procs = procs->next;
		i++;
	}
	return i;
}

int check_is_live(t_proc **procs, unsigned short is_beep)
{
	t_proc *tmp;
	t_proc *prev;
	t_proc *address;

	tmp = *procs;
	prev = tmp;
	while (tmp)
	{
		if (tmp->is_live)
		{
			tmp->is_live = 0;
			prev = tmp;
			address = tmp->next;
		}
		else
		{
			if (*procs == tmp)
				*procs = tmp->next;
			prev->next = tmp->next;
			address = tmp->next;
			free(tmp);
			if (is_beep == 1)
				beep();//TODO вивести звукове супроводження смерті
		}
		tmp = address;
	}
	if (*procs == NULL)
		return (0);
	return (1);
}

int		check_cycle_to_die(t_bs *bs, long *cycle_to_die,
						unsigned int *max_check,
						unsigned int *cycle_to_die_curr)
{
	t_chmp *tmp_champ;

	tmp_champ = bs->list_champs;
	if (*cycle_to_die_curr == *cycle_to_die)
	{
		while (tmp_champ)
		{
			tmp_champ->live = 0;
			tmp_champ = tmp_champ->next;
		}
		if (check_is_live(&bs->list_proc, bs->is_beep) == 0)
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

void	global_cycles_with_visual(t_bs *bs)
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
		ncurs->cyc_to_die = cycle_to_die;
		create_box(ncurs->window, 1);
		ch = getch();
		if (kb_proc(ncurs,ch) && ch == 27)
		{
			break;
		}
		if (ch != 's')
			usleep(1000000/ncurs->n_cyc);
		if (g_count == 0)
		{
			draw_mass(bs, 0, 0);
			ncurses_stats(ncurs->window, ncurs, bs, 1);
		}

		if (ncurs->flag || ch == 's')
		{
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
			if (g_count != 0)
			{
				draw_mass(bs, 0, 0);
				ncurses_stats(ncurs->window, ncurs, bs, 1);
			}
		ch = 0;
	}
	if (ch == 0)
	{++g_count;
	who_win(bs->list_champs, &bs->winner);
	//ncurses_stats(ncurs->window, ncurs, bs, 0);
	ncurses_result(ncurs, bs);
	while (getch() < 0)
	{

	}}
	endwin();
}

void	global_cycles_without_visual(t_bs *bs)
{
	long cycle_to_die;
	unsigned int cycle_to_die_curr;
	unsigned int max_check;

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
			break;
		}
		if (bs->is_print && bs->cycle_print % g_count == 0)
			print_map(bs->map);
		if (check_cycle_to_die(bs, &cycle_to_die, &max_check,
							   &cycle_to_die_curr) == 0)
			break;
	}
	++g_count;
//	ft_printf("g_count = %u\n", g_count);
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
	reverse_champs(&bs->list_champs);
	if (bs->is_num_flag)
		set_chmps_with_flag_num(bs);
	set_chmps_without_flag_num(bs);
	//print_map(bs->map);
	if (bs->is_visual)
		global_cycles_with_visual(bs);
	else
		global_cycles_without_visual(bs);
}