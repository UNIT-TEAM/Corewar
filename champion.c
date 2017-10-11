#include "corewar.h"

void	add_new_champ(t_chmp **first, unsigned int num_player, t_proc **proc)
{
	t_chmp	*tmp_cmp;
	t_proc	*tmp_proc;
	int 	i;

	if (!(tmp_cmp = (t_chmp *)malloc(sizeof(t_chmp))))
		ft_error(5, NULL);
	tmp_cmp->live = 0;
	if (*first && !num_player)
		tmp_cmp->num = (*first)->num + 1;
	else if (!num_player)
		tmp_cmp->num = 1;
	else
		tmp_cmp->num = num_player;
	if (!(tmp_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp_proc->carry = 0;
	tmp_proc->is_live = 1;
	tmp_proc->cycle_to_die = 0;
	tmp_proc->inst_cycle = 0;
	tmp_proc->id = tmp_cmp->num;
	i = -1;
	while (++i < REG_NUMBER)
		tmp_proc->regs[i] = 0;
	tmp_proc->next = *proc;
	*proc = tmp_proc;
	tmp_cmp->next = *first;
	*first = tmp_cmp;
}

//TODO розібратися з нумерацією ботов!!!