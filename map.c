#include "corewar.h"

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
	if (g_count % CYCLE_TO_DIE == 0)
	{
		if (nbr_live >= NBR_LIVE) {
			nbr_live = 0;
			*cycle_to_die -= CYCLE_DELTA;
		}
		else if (*max_check == 0)
			return (1);
		else if (nbr_live < NBR_LIVE)
		{
			nbr_live = 0;
			*max_check--;
		}
		else if (nbr_live >= NBR_LIVE)
		{
			nbr_live = 0;
			*max_check = MAX_CHECKS;
			*cycle_to_die -= CYCLE_DELTA;
		}
	}
	return 0;
}

void	global_cycles(t_bs *bs)
{
	unsigned int cycle_to_die;
	unsigned int max_check;

	cycle_to_die = CYCLE_TO_DIE;
	max_check = MAX_CHECKS;
	while (cycle_to_die != 0 && cycle_to_die < CYCLE_DELTA && max_check > 0)//зробити правельну перевірку для виходу з циклу при відніманні дельта
	{
		//TODO перевірка інструкцій
		//if (bs->is_dump && bs->dump == g_count)
			//TODO вивести карту і завершити програму
		//if (bs->is_dump_go && bs->dump_go % g_count == 0)
			//TODO виведемо карту на циклі dump_go і продовжимо програму

		if (check_cycle_to_die(bs->list_champs, &cycle_to_die, &max_check))
			break;
		g_count++;
	}
}

void    add_map_mapstr(t_bs *bs){
    int a;

    a = 0;
    bs->map_state = malloc(sizeof(t_map));
    bs->map_state->cycle_n = g_count;
    bs->map_state->map = malloc(sizeof(unsigned char)*MEM_SIZE);
    while (a < MEM_SIZE)
    {
        bs->map_state->map[a] = bs->map[a];
        a++;
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
    add_map_mapstr(bs);
	global_cycles(bs);
}

//TODO зробити загалиний цикл
//TODO потім інші всі цикли і процеси. спочатку процесів скільки ж як гравців
//TODO переробити список структур в масив струтук -->>нахер не треба переробляти
//TODO функція перевірки гравців на кількість життів