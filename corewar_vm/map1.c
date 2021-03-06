/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysavenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:59:20 by ysavenko          #+#    #+#             */
/*   Updated: 2017/10/23 19:36:52 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void		print_map(unsigned char *map)
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

void		for_check_inst_proc(t_bs *bs, t_proc **procs, unsigned char *map,
				t_proc *tmp)
{
	if (tmp->opcode == g_tab[7].opcode)
		ft_add_sub_and_or_xor(map, tmp, 7);
	else if (tmp->opcode == g_tab[8].opcode)
		ft_zjump(map, tmp, 8);
	else if (tmp->opcode == g_tab[9].opcode)
		ft_ldi_lldi(map, tmp, 9);
	else if (tmp->opcode == g_tab[10].opcode)
		ft_sti(bs, tmp, 10);
	else if (tmp->opcode == g_tab[11].opcode)
		ft_fork(map, procs, tmp, 11);
	else if (tmp->opcode == g_tab[12].opcode)
		ft_ld_lld(map, tmp, 12);
	else if (tmp->opcode == g_tab[13].opcode)
		ft_ldi_lldi(map, tmp, 13);
	else if (tmp->opcode == g_tab[14].opcode)
		ft_lfork(map, procs, tmp, 14);
	else if (tmp->opcode == g_tab[15].opcode)
		ft_aff(map, tmp, 15, bs->is_aff);
	else
		tmp->pc = (tmp->pc + 1) % MEM_SIZE;
}

void		check_inst_proc(t_bs *bs, t_proc **procs, unsigned char *map,
							t_chmp *champs)
{
	t_proc	*tmp;

	tmp = *procs;
	while (tmp)
	{
		if (tmp->inst_cycle == 0)
			tmp->opcode = map[tmp->pc];
		if (tmp->opcode == g_tab[0].opcode)
			ft_live(bs, tmp, 0, champs);
		else if (tmp->opcode == g_tab[1].opcode)
			ft_ld_lld(map, tmp, 1);
		else if (tmp->opcode == g_tab[2].opcode)
			ft_st(bs, tmp, 2);
		else if (tmp->opcode == g_tab[3].opcode)
			ft_add_sub_and_or_xor(map, tmp, 3);
		else if (tmp->opcode == g_tab[4].opcode)
			ft_add_sub_and_or_xor(map, tmp, 4);
		else if (tmp->opcode == g_tab[5].opcode)
			ft_add_sub_and_or_xor(map, tmp, 5);
		else if (tmp->opcode == g_tab[6].opcode)
			ft_add_sub_and_or_xor(map, tmp, 6);
		else
			for_check_inst_proc(bs, procs, map, tmp);
		tmp = tmp->next;
	}
}

int			check_is_live(t_proc **procs, t_proc *tmp)
{
	t_proc *prev;
	t_proc *address;

	tmp = *procs;
	prev = tmp;
	while (tmp)
	{
		address = tmp->next;
		if (tmp->is_live)
		{
			tmp->is_live = 0;
			prev = tmp;
		}
		else
		{
			if (*procs == tmp)
				*procs = tmp->next;
			prev->next = tmp->next;
			free(tmp);
		}
		tmp = address;
	}
	return (*procs == NULL ? 0 : 1);
}
