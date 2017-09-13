#include "corewar.h"

void	add_new_champ(t_chmp **first, unsigned int num_player)
{
	t_chmp	*tmp;
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
	if (!(tmp->proc_1 = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp->proc_1->carry = 0;
	i = -1;
	while (++i < REG_NUMBER)
		tmp->proc_1->regs[i] = 0;
	tmp->next = *first;
	*first = tmp;
}

//TODO розібратися з нумерацією ботов!!!