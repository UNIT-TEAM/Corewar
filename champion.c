#include "corewar.h"

void	make_champ(t_chmp *player)
{
	t_chmp	*tmp;

	if (!(tmp = (t_chmp *)malloc(sizeof(t_chmp))))
		ft_error(5, "NULL");
	tmp->nx = player->nx;
	player->nx = tmp;
}

//TODO створити список гравців
//TODO уточнити питання з мейна
//TODO переробити фунцію ft_sprint під списки