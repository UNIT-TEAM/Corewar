/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddovzhik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 22:00:52 by ddovzhik          #+#    #+#             */
/*   Updated: 2017/10/23 22:00:55 by ddovzhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_ld_lld(unsigned char *map, t_proc *proc, unsigned short op_index,
					short flag_long)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	if (!(heap_args = take_argument(map, codage, proc, op_index, flag_long)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	proc->regs[arg[1]] = arg[0];
	proc->carry = (unsigned char)(arg[0] == 0 ? 1 : 0);
	shift_pc(codage, proc, op_index);
}

void	ft_ldi_lldi(unsigned char *map, t_proc *proc, unsigned short op_index,
					short flag_long)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	if (!(heap_args = take_argument(map, codage, proc, op_index, flag_long)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ? proc->regs[arg[0]] : arg[0];
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ? proc->regs[arg[1]] : arg[1];
	proc->regs[arg[2]] = take_value_from_address(map, proc,
								(unsigned short)(arg[0] + arg[1]), flag_long);
	proc->carry = (unsigned char)(proc->regs[arg[2]] == 0 ? 1 : 0);
	shift_pc(codage, proc, op_index);
}

void	set_bytes_on_map(t_bs *bs, unsigned int i, t_proc *proc,
							unsigned int *arg)
{
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 24);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 16);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 8);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i % MEM_SIZE] = (unsigned char)arg[0];
}

void	ft_st(t_bs *bs, t_proc *proc, unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;
	unsigned int	i;

	if (for_instruct(bs->map, proc, op_index, &codage) == 0)
		return ;
	g_tab[op_index].dir_size = 1;
	if (codage == 0x70)
		codage = 0x60;
	if (!(heap_args = take_argument(bs->map, codage, proc, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	arg[0] = proc->regs[arg[0]];
	if (codage == 0x50)
	{
		proc->regs[arg[1]] = arg[0];
		shift_pc(codage, proc, op_index);
		return ;
	}
	i = (unsigned int)((long)proc->pc + (short)arg[1] % IDX_MOD < 0 ?
			MEM_SIZE + ((long)proc->pc + (short)arg[1] % IDX_MOD) % MEM_SIZE :
						((long)proc->pc + (short)arg[1] % IDX_MOD) % MEM_SIZE);
	set_bytes_on_map(bs, i, proc, arg);
	shift_pc(codage, proc, op_index);
}

void	ft_sti(t_bs *bs, t_proc *proc, unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;
	unsigned int	i;

	if (for_instruct(bs->map, proc, op_index, &codage) == 0)
		return ;
	if (!(heap_args = take_argument(bs->map, codage, proc, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ? proc->regs[arg[0]] : arg[0];
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ? proc->regs[arg[1]] : arg[1];
	arg[2] = (((codage >> 2) & 0x3) == REG_CODE) ? proc->regs[arg[2]] : arg[2];
	i = (unsigned int)
			(((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) < 0 ?
			MEM_SIZE +
			((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE :
			((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE);
	set_bytes_on_map(bs, i, proc, arg);
	shift_pc(codage, proc, op_index);
}
