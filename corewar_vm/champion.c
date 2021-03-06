/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddovzhik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 23:55:21 by ddovzhik          #+#    #+#             */
/*   Updated: 2017/10/24 15:34:06 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	add_new_process(t_proc **proc)
{
	t_proc	*tmp_proc;
	int		i;

	if (!(tmp_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp_proc->carry = 0;
	tmp_proc->is_live = 0;
	tmp_proc->inst_cycle = 0;
	i = -1;
	while (++i < REG_NUMBER)
		tmp_proc->regs[i] = 0;
	tmp_proc->next = *proc;
	*proc = tmp_proc;
}

void	a_n_c(t_chmp **first, unsigned int flag_num, t_proc **proc,
			char *av)
{
	t_chmp	*tmp_cmp;
	t_chmp	*curr;
	int		fd;

	((fd = open(av, O_RDONLY)) < 0) ? ft_error(2, NULL) : 0;
	if (!(tmp_cmp = (t_chmp *)malloc(sizeof(t_chmp))))
		ft_error(5, NULL);
	tmp_cmp->live = 0;
	tmp_cmp->cycle_live = 0;
	tmp_cmp->flag_num = flag_num;
	if (flag_num != 0)
	{
		curr = *first;
		while (curr)
			if (curr->flag_num == flag_num)
				ft_error(12, NULL);
			else
				curr = curr->next;
	}
	tmp_cmp->next = *first;
	*first = tmp_cmp;
	add_new_process(proc);
	close(fd);
}

void	print_champs(t_chmp *champs, unsigned short is_visual)
{
	t_chmp			*tmp;

	tmp = champs;
	if (is_visual == 0)
		ft_printf(YEL"Introducing contestants...\n"RC);
	while (tmp)
	{
		if (is_visual == 0)
			ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\")\n",
					tmp->num, tmp->head.prog_size, tmp->head.prog_name,
					tmp->head.comment);
		tmp = tmp->next;
	}
}
