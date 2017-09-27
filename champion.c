#include "corewar.h"

void	add_new_champ(t_chmp **first, unsigned int num_player, t_proc **proc)
{
	t_chmp	*tmp;
	t_proc	*tp;
	int 	i;

	if (!(tmp = (t_chmp *)malloc(sizeof(t_chmp))))
		ft_error(5, NULL);
	tmp->live = 0;
	if (*first && !num_player)
		tmp->num = (*first)->num + 1;
	else if (!num_player)
		tmp->num = 1;
	else
		tmp->num = num_player;
	if (!(tp = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tp->live = 1;
	tp->carry = 0;
	tp->cycle_to_die = CYCLE_TO_DIE;
	i = -1;
	while (++i < REG_NUMBER)
		tp->regs[i] = 0;
	tp->next = *proc;
	*proc = tp;
	tmp->next = *first;
	*first = tmp;
}

//TODO розібратися з нумерацією ботов!!!