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

void    check_inst_proc(t_proc *procs, unsigned char *map)
{
    t_proc *tmp;
	t_proc *prev;

    tmp = procs;
	prev = tmp;
    while (tmp)
    {
        if (tmp->cycle_to_die != CYCLE_TO_DIE)
// TODO в кожній інструкції перевіряти inst_cycle,
// якщо він дорівнює циклу інструкцій то дана інструкція
// виконується в іншому разі inst_cycle збільшується на 1
		{
			if (map[tmp->pc] == op_tab[0].opcode);//TODO функція live
				//TODO преревірка чи процесу чи гравцю кажеться що живий
			else if (map[tmp->pc] == op_tab[1].opcode);//TODO функція ld
			else if (map[tmp->pc] == op_tab[2].opcode);//TODO функція st
			else if (map[tmp->pc] == op_tab[3].opcode);//TODO функція add
			else if (map[tmp->pc] == op_tab[4].opcode);//TODO функція sub
			else if (map[tmp->pc] == op_tab[5].opcode);//TODO функція and
			else if (map[tmp->pc] == op_tab[6].opcode);//TODO функція or
			else if (map[tmp->pc] == op_tab[7].opcode);//TODO функція xor
			else if (map[tmp->pc] == op_tab[8].opcode);//TODO функція zjmp
			else if (map[tmp->pc] == op_tab[9].opcode);//TODO функція ldi
			else if (map[tmp->pc] == op_tab[10].opcode)
				sti(map, tmp, op_tab[10].opcode);
			else if (map[tmp->pc] == op_tab[11].opcode);//TODO функція fork
			else if (map[tmp->pc] == op_tab[12].opcode);//TODO функція lld
			else if (map[tmp->pc] == op_tab[13].opcode);//TODO функція lldi
			else if (map[tmp->pc] == op_tab[14].opcode);//TODO функція lfork
			else if (map[tmp->pc] == op_tab[15].opcode);//TODO функція aff
			else
				tmp->pc = (tmp->pc + 1) % MEM_SIZE;
			++tmp->cycle_to_die;
			prev = tmp;
			tmp = tmp->next;
		}
		else
		{
			prev->next = tmp->next;
			free(tmp);
		}
    }
}

void	check_cycle_to_die(t_chmp *players, unsigned int *cycle_to_die,
							unsigned int *max_check)
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
	if ((g_count + 1) % (CYCLE_TO_DIE + 1) == 0)
	{
		if (nbr_live >= NBR_LIVE)
		{
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else
			(*max_check)--;
	}
}

void	global_cycles(t_bs *bs)
{
	unsigned int cycle_to_die;
	unsigned int max_check;

	cycle_to_die = CYCLE_TO_DIE;
	max_check = MAX_CHECKS;
	while ((long)cycle_to_die - CYCLE_DELTA > 0 && max_check > 0)
	{
		++g_count;
		print_map(bs->map);
		check_inst_proc(bs->list_proc, bs->map);
		print_map(bs->map);
		//if (bs->is_dump && bs->dump == g_count)
			//TODO вивести карту і завершити програму
		//if (bs->is_dump_go && bs->dump_go % g_count == 0)
			//TODO виведемо карту на циклі dump_go і продовжимо програму
		check_cycle_to_die(bs->list_champs, &cycle_to_die, &max_check);
	}
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
			bs->map[pftr + k] = tmp->instructions[k];
		tp = tp->next;
		tmp = tmp->next;
	}
	global_cycles(bs);
}
//TODO потім інші всі цикли і процеси. спочатку процесів скільки ж як гравців