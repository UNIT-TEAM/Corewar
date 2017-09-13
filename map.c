#include "corewar.h"

void	global_cycles(t_bs *bs)
{
	unsigned int cycle_to_die;

	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die != 0)//зробити правельну перевірку для виходу з циклу при відніманні дельта
	{
		g_count++;
		//
		cycle_to_die -= CYCLE_DELTA;
	}
}

void	ft_fill_map(t_bs *bs)
{
	int 			i;
	unsigned int	pftr;
	int 			k;
	t_chmp			*tmp;

	i = -1;
	pftr = 0;
	tmp = bs->list_champs;
	while (++i < bs->np)
	{
		pftr = (i == 0) ? 0 : pftr + MEM_SIZE / bs->np;
		tmp->proc_1->pc = pftr;
		k = -1;
		while (++k < tmp->head.prog_size)
			bs->map[pftr + k] = tmp->instructions[k];
		tmp = tmp->next;
	}
	global_cycles(bs);
}

//TODO зробити загалиний цикл
//TODO потім інші всі цикли і процеси. спочатку процесів скільки ж як гравців
//TODO переробити список структур в масив струтук
//TODO функція перевірки гравців на кількість життів