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

void    check_inst_proc(t_proc **procs, unsigned char *map, t_chmp *champs)
{
    t_proc *tmp;

    tmp = *procs;
    while (tmp)
    {
		if (map[tmp->pc] == op_tab[0].opcode)
			ft_live(map, tmp, 0, champs);
		else if (map[tmp->pc] == op_tab[1].opcode)
			ft_ld_lld(map, tmp, 1, 0);
		else if (map[tmp->pc] == op_tab[2].opcode)
			ft_st_sti(map, tmp, 2, 0);
		else if (map[tmp->pc] == op_tab[3].opcode)
			ft_add_sub(map, tmp, 3, 0);
		else if (map[tmp->pc] == op_tab[4].opcode)
			ft_add_sub(map, tmp, 4, 1);
		else if (map[tmp->pc] == op_tab[5].opcode)
			ft_and_or_xor(map, tmp, 5, 0);
		else if (map[tmp->pc] == op_tab[6].opcode)
			ft_and_or_xor(map, tmp, 6, 1);
		else if (map[tmp->pc] == op_tab[7].opcode)
			ft_and_or_xor(map, tmp, 7, 2);
		else if (map[tmp->pc] == op_tab[8].opcode)
			ft_zjump(map, tmp, 8);
		else if (map[tmp->pc] == op_tab[9].opcode)
			ft_ldi_lldi(map, tmp, 9, 0);
		else if (map[tmp->pc] == op_tab[10].opcode)
			ft_st_sti(map, tmp, 10, 1);
		else if (map[tmp->pc] == op_tab[11].opcode)
			ft_fork(map, procs, tmp, 11);
		else if (map[tmp->pc] == op_tab[12].opcode)
			ft_ld_lld(map, tmp, 12, 1);
		else if (map[tmp->pc] == op_tab[13].opcode)
			ft_ldi_lldi(map, tmp, 13, 1);
		else if (map[tmp->pc] == op_tab[14].opcode)
			ft_lfork(map, procs, tmp, 14);
		else if (map[tmp->pc] == op_tab[15].opcode)
			ft_aff(map, tmp, 15);
		else
			tmp->pc = (tmp->pc + 1) % MEM_SIZE;
    }
}

//TODO isnt_cycle ніде не ітерується!!!!!!!!!!!!!!!!!!!

void	check_is_live(t_proc **procs)
{
	t_proc *tmp;
	t_proc *prev;

	tmp = *procs;
	prev = tmp;
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
}

void check_cycle_to_die(t_bs *bs, long *cycle_to_die,
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
				nbr_live += tmp->live;
			tmp = tmp->next;
		}
		check_is_live(&bs->list_proc);
		if (nbr_live >= NBR_LIVE || *max_check == 0)
		{
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else
			--(*max_check);
		*cycle_to_die_curr = 0;
	}
}

void	who_win(t_proc *procs, unsigned int *winner)
{
	t_proc *tmp;
	unsigned int max_cycle;

	tmp = procs;
	*winner = tmp->id;
	max_cycle = tmp->cycle_live;
	tmp = tmp->next;
	while (tmp)
	{
		if (max_cycle < tmp->cycle_live)
		{
			*winner = tmp->id;
			max_cycle = tmp->cycle_live;
		}
		else if (max_cycle == tmp->cycle_live)
			*winner = (tmp->id > *winner) ? tmp->id : *winner;
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
	while (cycle_to_die > 0)
	{
		++g_count;
		++cycle_to_die_curr;
		check_inst_proc(&bs->list_proc, bs->map, bs->list_champs);
//		if (bs->is_dump && bs->dump == g_count)
//		{
//			print_map(bs->map);
//			break;
//		}
//		if (bs->is_dump_go && bs->dump_go % g_count == 0)
//			print_map(bs->map);
		check_cycle_to_die(bs, &cycle_to_die, &max_check,
						   &cycle_to_die_curr);
	}
	who_win(bs->list_proc, &bs->winner);
}

//void	flag_num(t_bs *bs)
//{
//
//}

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
			tmp_proc->id = tmp_chmp->num;
			tmp_proc->pc = (tmp_chmp->flag_num - 1) * (MEM_SIZE / bs->np);
			k = -1;
			while (++k < tmp_chmp->head.prog_size)
				bs->map[tmp_proc->pc + k] = tmp_chmp->instructions[k];
		}
		tmp_chmp = tmp_chmp->next;
		tmp_proc = tmp_proc->next;
	}
	print_map(bs->map);
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
			tmp_proc->id = tmp_chmp->num;
			k = -1;
			while (++k < tmp_chmp->head.prog_size)
				bs->map[tmp_proc->pc + k] = tmp_chmp->instructions[k];
			i += MEM_SIZE / bs->np;
		}
		tmp_chmp = tmp_chmp->next;
		tmp_proc = tmp_proc->next;
	}
	print_map(bs->map);
}

void	ft_fill_map(t_bs *bs)
{
	if (bs->is_num_flag)
		set_chmps_with_flag_num(bs);
	set_chmps_without_flag_num(bs);
	global_cycles(bs);
}