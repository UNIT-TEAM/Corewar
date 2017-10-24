/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddovzhik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 00:14:11 by ddovzhik          #+#    #+#             */
/*   Updated: 2017/10/24 14:51:59 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				take_arg_reg(unsigned char *map, unsigned int *arg,
								unsigned int *tmp_pc)
{
	unsigned char index;

	index = map[*tmp_pc];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = (unsigned int)(index - 1);
	*tmp_pc = (*tmp_pc + 1) % MEM_SIZE;
	return (1);
}

int				take_arg_dir(unsigned char *map, unsigned int *arg,
								unsigned int *tmp_pc, unsigned short op_index)
{
	unsigned char	code[4];

	if (g_tab[op_index].dir_size == 0)
	{
		code[0] = map[(*tmp_pc + 3) % MEM_SIZE];
		code[1] = map[(*tmp_pc + 2) % MEM_SIZE];
		code[2] = map[(*tmp_pc + 1) % MEM_SIZE];
		code[3] = map[*tmp_pc];
		*arg = *((unsigned int *)code);
		*tmp_pc = (*tmp_pc + 4) % MEM_SIZE;
	}
	else
	{
		code[0] = map[(*tmp_pc + 1) % MEM_SIZE];
		code[1] = map[*tmp_pc];
		*arg = *((unsigned short *)code);
		*tmp_pc = (*tmp_pc + 2) % MEM_SIZE;
	}
	return (1);
}

int				take_arg_ind(unsigned char *map, unsigned int *arg,
						unsigned int *tmp_pc, t_proc *proc, short flag_long)
{
	unsigned char	code[2];
	unsigned short	p;

	code[0] = map[(*tmp_pc + 1) % MEM_SIZE];
	code[1] = map[*tmp_pc];
	p = *((unsigned short *)code);
	*arg = take_value_from_address(map, proc, p, flag_long);
	*tmp_pc = (*tmp_pc + 2) % MEM_SIZE;
	return (1);
}

unsigned int	*take_argument(unsigned char *map, unsigned char codage,
				t_proc *proc, unsigned short op_index, short flag_long)
{
	int				res;
	int				i;
	int				j;
	unsigned int	tmp_pc;
	unsigned int	*arg;

	if ((arg = (unsigned int *)malloc(
			sizeof(unsigned int) * g_tab[op_index].count_arg)) == NULL)
		ft_error(5, NULL);
	tmp_pc = (g_tab[op_index].is_codage ?
				proc->pc + 2 : proc->pc + 1) % MEM_SIZE;
	j = 8;
	i = -1;
	while (++i < g_tab[op_index].count_arg)
	{
		j -= 2;
		res = 0;
		if (((codage >> j) & 0x3) == REG_CODE)
			res = take_arg_reg(map, arg + i, &tmp_pc);
		else if (((codage >> j) & 0x3) == DIR_CODE)
			res = take_arg_dir(map, arg + i, &tmp_pc, op_index);
		else if (((codage >> j) & 0x3) == IND_CODE)
			res = take_arg_ind(map, arg + i, &tmp_pc, proc, flag_long);
		if (res == 0)
		{
			shift_pc(codage, proc, op_index);
			return (NULL);
		}
	}
	return (arg);
}

int				check_codage(unsigned char codage, t_proc *proc,
						unsigned short index)
{
	unsigned char	tmp;
	int				i;
	int				j;

	i = 8;
	j = 0;
	while (j < g_tab[index].count_arg)
	{
		i -= 2;
		tmp = (unsigned char)((codage >> i) & 0x3);
		if (tmp == REG_CODE && ((g_tab[index].arg[j] & T_REG) == T_REG))
			;
		else if (tmp == DIR_CODE && ((g_tab[index].arg[j] & T_DIR) == T_DIR))
			;
		else if (tmp == IND_CODE && ((g_tab[index].arg[j] & T_IND) == T_IND))
			;
		else
		{
			shift_pc(codage, proc, index);
			return (0);
		}
		++j;
	}
	return (1);
}
