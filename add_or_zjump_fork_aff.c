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

void	ft_add_sub_and_or_xor(unsigned char *map, t_proc *proc,
								unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	if (!(heap_args = take_argument(map, codage, proc, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ? proc->regs[arg[0]] : arg[0];
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ? proc->regs[arg[1]] : arg[1];
	if (ft_strequ(g_tab[op_index].name, "add"))
		proc->regs[arg[2]] = arg[0] + arg[1];
	else if (ft_strequ(g_tab[op_index].name, "sub"))
		proc->regs[arg[2]] = arg[0] - arg[1];
	else if (ft_strequ(g_tab[op_index].name, "and"))
		proc->regs[arg[2]] = arg[0] & arg[1];
	else if (ft_strequ(g_tab[op_index].name, "or"))
		proc->regs[arg[2]] = arg[0] | arg[1];
	else if (ft_strequ(g_tab[op_index].name, "xor"))
		proc->regs[arg[2]] = arg[0] ^ arg[1];
	proc->carry = (unsigned short)(proc->regs[arg[2]] == 0 ? 1 : 0);
	shift_pc(codage, proc, op_index);
}

void	ft_zjump(unsigned char *map, t_proc *proc, unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;

	if (for_instruct(map, proc, op_index, NULL) == 0)
		return ;
	if (!(heap_args = take_argument(map, DIR_CODE << 6, proc, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	if (proc->carry == 1)
		proc->pc = (unsigned int)((long)proc->pc + (short)arg[0] % IDX_MOD < 0 ?
			MEM_SIZE + ((long)proc->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE :
						((long)proc->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE);
	else
		shift_pc(DIR_CODE << 6, proc, op_index);
}

void	ft_fork(unsigned char *map, t_proc **procs, t_proc *tmp,
				unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	t_proc			*new_proc;
	int				i;

	if (for_instruct(map, tmp, op_index, NULL) == 0)
		return ;
	if (!(heap_args = take_argument(map, DIR_CODE << 6, tmp, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	new_proc->pc = (unsigned int)((long)tmp->pc + (short)arg[0] % IDX_MOD < 0 ?
			MEM_SIZE + ((long)tmp->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE :
						((long)tmp->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE);
	i = -1;
	while (++i < REG_NUMBER)
		new_proc->regs[i] = tmp->regs[i];
	new_proc->carry = tmp->carry;
	new_proc->id = tmp->id;
	new_proc->inst_cycle = tmp->inst_cycle;
	new_proc->is_live = tmp->is_live;
	new_proc->next = *procs;
	*procs = new_proc;
	shift_pc(DIR_CODE << 6, tmp, op_index);
}

void	ft_lfork(unsigned char *map, t_proc **procs, t_proc *tmp,
					unsigned short op_index)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	t_proc			*new_proc;
	int				i;

	if (for_instruct(map, tmp, op_index, NULL) == 0)
		return ;
	if (!(heap_args = take_argument(map, DIR_CODE << 6, tmp, op_index, 1)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	new_proc->pc = (unsigned int)((long)tmp->pc + (short)arg[0] < 0 ?
						MEM_SIZE + ((long)tmp->pc + (short)arg[0]) % MEM_SIZE :
									((long)tmp->pc + (short)arg[0]) % MEM_SIZE);
	i = -1;
	while (++i < REG_NUMBER)
		new_proc->regs[i] = tmp->regs[i];
	new_proc->carry = tmp->carry;
	new_proc->id = tmp->id;
	new_proc->inst_cycle = tmp->inst_cycle;
	new_proc->is_live = tmp->is_live;
	new_proc->next = *procs;
	*procs = new_proc;
	shift_pc(DIR_CODE << 6, tmp, op_index);
}

void	ft_aff(unsigned char *map, t_proc *proc, unsigned short op_index,
				unsigned short is_aff)
{
	unsigned int	arg[g_tab[op_index].count_arg];
	unsigned int	*heap_args;
	unsigned char	codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	if (!(heap_args = take_argument(map, codage, proc, op_index, 0)))
		return ;
	parse_heap_to_stack_args(arg, &heap_args, g_tab[op_index].count_arg);
	if (is_aff == 1)
		ft_printf("aff is "YEL"%u"RC, arg[0]);
	shift_pc(codage, proc, op_index);
}
