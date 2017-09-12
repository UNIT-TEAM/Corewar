#include "corewar.h"

void	fill_inst_and_code(t_chmp *champs, unsigned char **inst_cmp,
		unsigned int *code_size, int l)
{
	t_chmp	*tmp;
	int 	i;

	i = -1;
	tmp = champs;
	while (tmp && ++i != l)
		tmp->next = champs;
	/*if (tmp && !(*inst_cmp = (unsigned char *)malloc(sizeof(unsigned char) *
													  tmp->head.prog_size)))
		ft_error(5, NULL);
	*/
	if (tmp)
	{
		*inst_cmp = tmp->instructions;
		*code_size = tmp->head.prog_size;
	}
}

void	ft_fill_map(t_bs *bs)
{
	int				i;
	unsigned int	pftr;
	int 			k;
	unsigned char	*inst_cmp;
	unsigned int	code_size;

	i = -1;
	k = -1;
	pftr = 0;
	while (++i < bs->np)
	{
		fill_inst_and_code(bs->list_champs, &inst_cmp, &code_size, i);
		pftr = (i == 0) ? 0 : pftr + MEM_SIZE / bs->np;
		while (++k < code_size)
			bs->map[pftr + k] = inst_cmp[k];
	}

}

//TODO зробити загалиний цикл
//TODO потім інші всі цикли і процеси. спочатку процесів скільки ж як гравців
//TODO переробити список структур в масив струтук
//TODO записати PC в цій же функції
