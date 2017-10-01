#include "corewar.h"

void    check_inst_proc(t_proc *procs, unsigned char *map)
{
    t_proc *tmp;
	t_proc *prev;

    tmp = procs;
	prev = tmp;
    while (tmp)
    {
        if (tmp->cycle_to_die != CYCLE_TO_DIE)
//TODO в кожній інструкції перевіряти inst_cycle, якщо він дорівнює циклу інструкцій то дана інструкція виконується в іншому разі inst_cycle збільшується на 1
		{
			if (tmp->pc == op_tab[0].opcode);//TODO функція live
				//TODO преревірка чи процесу чи гравцю кажеться що живий
			else if (tmp->pc == op_tab[1].opcode);//TODO функція ld
			else if (tmp->pc == op_tab[2].opcode);//TODO функція st
			else if (tmp->pc == op_tab[3].opcode);//TODO функція add
			else if (tmp->pc == op_tab[4].opcode);//TODO функція sub
			else if (tmp->pc == op_tab[5].opcode);//TODO функція and
			else if (tmp->pc == op_tab[6].opcode);//TODO функція or
			else if (tmp->pc == op_tab[7].opcode);//TODO функція xor
			else if (tmp->pc == op_tab[8].opcode);//TODO функція zjmp
			else if (tmp->pc == op_tab[9].opcode);//TODO функція ldi
			else if (tmp->pc == op_tab[10].opcode);//TODO функція sti
			else if (tmp->pc == op_tab[11].opcode);//TODO функція fork
			else if (tmp->pc == op_tab[12].opcode);//TODO функція lld
			else if (tmp->pc == op_tab[13].opcode);//TODO функція lldi
			else if (tmp->pc == op_tab[14].opcode);//TODO функція lfork
			else if (tmp->pc == op_tab[15].opcode);//TODO функція aff
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

int 	check_cycle_to_die(t_chmp *players, unsigned int *cycle_to_die,
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
	if ((g_count + 1) % (CYCLE_TO_DIE + 1) != 0)
	{
		if (nbr_live >= NBR_LIVE) {
			nbr_live = 0;
			(*cycle_to_die) -= CYCLE_DELTA;
		}
		else if (*max_check == 0)
			return (1);
		else if (nbr_live < NBR_LIVE)
		{
			nbr_live = 0;
			(*max_check)--;
		}
		else if (nbr_live >= NBR_LIVE)
		{
			nbr_live = 0;
			*max_check = MAX_CHECKS;
			(*cycle_to_die) -= CYCLE_DELTA;
		}
	}
	else
		(*cycle_to_die) -= CYCLE_DELTA;
	return 0;
}

void	global_cycles(t_bs *bs)
{
	unsigned int cycle_to_die;
	unsigned int max_check;

	cycle_to_die = CYCLE_TO_DIE;
	max_check = MAX_CHECKS;
	while ((long)cycle_to_die - CYCLE_DELTA > 0 && max_check > 0)
	{
		check_inst_proc(bs->list_proc, bs->map);
		//if (bs->is_dump && bs->dump == g_count)
			//TODO вивести карту і завершити програму
		//if (bs->is_dump_go && bs->dump_go % g_count == 0)
			//TODO виведемо карту на циклі dump_go і продовжимо програму

		if (check_cycle_to_die(bs->list_champs, &cycle_to_die, &max_check))
			break;
		g_count++;
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

//TODO зробити загалиний цикл
//TODO потім інші всі цикли і процеси. спочатку процесів скільки ж як гравців
//TODO функція перевірки гравців на кількість життів