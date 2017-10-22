#include "corewar.h"

int	for_instruct(unsigned char *map, t_proc *proc, unsigned short op_index,
					unsigned char *codage)
{


	if (++proc->inst_cycle != op_tab[op_index].cycles)
		return (0);
	*codage = map[(proc->pc + 1) % MEM_SIZE];
	if (op_tab[op_index].is_codage && !check_codage(*codage, proc, op_index))
	{
		proc->inst_cycle = 0;
		return (0);
	}
	return (1);
}

void	parse_heap_to_stack_args(unsigned int *args, unsigned int **heap_args,
								 int count_arg)
{
	int i;

	i = 0;
	while (i < count_arg)
	{
		args[i] = (*heap_args)[i];
		++i;
	}
	free(*heap_args);
	*heap_args = NULL;
}

void	ft_live(t_bs *bs, t_proc *proc, unsigned short op_index,
				   t_chmp *champs)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	t_chmp *curr;

	if (for_instruct(bs->map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if ((heap_args = take_argument(bs->map, codage, proc, op_index, 0))	== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	proc->is_live = 1;
	++bs->num_live;
	curr = champs;
	while (curr)
	{
		if (curr->num * -1 == arg[0])
		{
			++curr->live;
			bs->color_map[proc->pc].live = g_count;
			curr->cycle_live = g_count;
		}
		curr = curr->next;
	}
	shift_pc(codage, proc, op_index);
}

void	ft_ld_lld_ldi_lldi(unsigned char *map, t_proc *proc,
						   unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	unsigned int load_value;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
//	print_map(map);
	proc->inst_cycle = 0;
	if (ft_strequ(op_tab[op_index].name, "ld") ||
			ft_strequ(op_tab[op_index].name, "ldi"))
	{
		if ((heap_args = take_argument(map, codage, proc, op_index, 0)) == NULL)
			return;
	}
	else
		if ((heap_args = take_argument(map, codage, proc, op_index, 1)) == NULL)
			return;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (ft_strequ(op_tab[op_index].name, "ldi") ||
			ft_strequ(op_tab[op_index].name, "lldi"))
	{
		arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ?
				 proc->regs[arg[0]] : arg[0];
		arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ?
				 proc->regs[arg[1]] : arg[1];
	}
	if (ft_strequ(op_tab[op_index].name, "ldi"))
		load_value = take_value_from_addres(map,
						proc, (unsigned short)(arg[0] + arg[1]), 0);
	else if (ft_strequ(op_tab[op_index].name, "lldi"))
		load_value =
				take_value_from_addres(map,
						proc, (unsigned short)(arg[0] + arg[1]), 1);
	else
		load_value = arg[0];
	if (ft_strequ(op_tab[op_index].name, "ld") ||
			ft_strequ(op_tab[op_index].name, "lld"))
		proc->regs[arg[1]] = load_value;
	else if (ft_strequ(op_tab[op_index].name, "ldi") ||
			 ft_strequ(op_tab[op_index].name, "lldi"))
		proc->regs[arg[2]] = load_value;
	proc->carry = (unsigned char)(load_value == 0 ? 1 : 0);
	shift_pc(codage, proc, op_index);
//	print_map(map);
}

void	ft_st_sti(t_bs *bs, t_proc *proc, unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	unsigned int i;

	if (for_instruct(bs->map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	if (ft_strequ(op_tab[op_index].name, "st") && codage == 0x70)
	{
		codage = 0x60;
		op_tab[op_index].dir_size = 1;
	}
	if ((heap_args = take_argument(bs->map, codage, proc, op_index, 0)) == NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ?
			 proc->regs[arg[0]] : arg[0];
	if (ft_strequ(op_tab[op_index].name, "st") && codage == 0x50)
	{
		proc->regs[arg[1]] = arg[0];
		shift_pc(codage, proc, op_index);
		return ;
	}
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ?
			 proc->regs[arg[1]] : arg[1];
	if (ft_strequ(op_tab[op_index].name, "sti"))
		arg[2] = (((codage >> 2) & 0x3) == REG_CODE) ?
				 proc->regs[arg[2]] : arg[2];
	if (ft_strequ(op_tab[op_index].name, "st"))
	{
		i = (unsigned int)((long)proc->pc + (short)arg[1] % IDX_MOD < 0 ?
						   MEM_SIZE +
						((long)proc->pc + (short)arg[1] % IDX_MOD) % MEM_SIZE :
						((long)proc->pc + (short)arg[1] % IDX_MOD) % MEM_SIZE);
	}
	else if (ft_strequ(op_tab[op_index].name, "sti"))
		i = (unsigned int)
				(((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) < 0 ?
			MEM_SIZE +
			((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE :
			((long)proc->pc + (short)(arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 24);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 16);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 8);
	(bs->is_visual) ? add_color(i % MEM_SIZE, proc->id, bs) : 0;
	bs->map[i % MEM_SIZE] = (unsigned char)arg[0];
	shift_pc(codage, proc, op_index);
}

void	ft_add_sub_and_or_xor(unsigned char *map, t_proc *proc,
							  unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	if ((heap_args = take_argument(map, codage, proc, op_index, 0)) == NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ?
			 proc->regs[arg[0]] : arg[0];
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ?
			 proc->regs[arg[1]] : arg[1];
	if (ft_strequ(op_tab[op_index].name, "add"))
		proc->regs[arg[2]] = arg[0] + arg[1];
	else if (ft_strequ(op_tab[op_index].name, "sub"))
		proc->regs[arg[2]] = arg[0] - arg[1];
	else if (ft_strequ(op_tab[op_index].name, "and"))
		proc->regs[arg[2]] = arg[0] & arg[1];
	else if (ft_strequ(op_tab[op_index].name, "or"))
		proc->regs[arg[2]] = arg[0] | arg[1];
	else if (ft_strequ(op_tab[op_index].name, "xor"))
		proc->regs[arg[2]] = arg[0] ^ arg[1];
	proc->carry = (unsigned short)(proc->regs[arg[2]] == 0 ? 1 : 0);
	shift_pc(codage, proc, op_index);
}

void	ft_zjump(unsigned char *map, t_proc *proc, unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if ((heap_args = take_argument(map, codage, proc, op_index, 0)) == NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (proc->carry == 1)
		proc->pc = (unsigned int)((long)proc->pc + (short)arg[0] % IDX_MOD < 0 ?
				   MEM_SIZE +
					   ((long)proc->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE :
				   ((long)proc->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE);
	else
		shift_pc(codage, proc, op_index);
}

void	ft_fork_lfork(unsigned char *map, t_proc **procs, t_proc *tmp,
				   unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	t_proc *new_proc;
	int i;

	if (for_instruct(map, tmp, op_index, &codage) == 0)
		return ;
	tmp->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if (ft_strequ(op_tab[op_index].name, "fork"))
	{
		if ((heap_args = take_argument(map, codage, tmp, op_index, 0)) == NULL)
			return;
	}
	else
		if ((heap_args = take_argument(map, codage, tmp, op_index, 1)) == NULL)
			return;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	if (ft_strequ(op_tab[op_index].name, "fork"))
		new_proc->pc = (unsigned int)((long)tmp->pc + (short)arg[0] % IDX_MOD < 0 ?
									  MEM_SIZE +
						((long)tmp->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE :
						((long)tmp->pc + (short)arg[0] % IDX_MOD) % MEM_SIZE);
	else if (ft_strequ(op_tab[op_index].name, "lfork"))
		new_proc->pc = (unsigned int)((long)tmp->pc + (short)arg[0] < 0 ?
									  MEM_SIZE +
								  ((long)tmp->pc + (short)arg[0]) % MEM_SIZE :
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
	shift_pc(codage, tmp, op_index);
}

void ft_aff(unsigned char *map, t_proc *proc, unsigned short op_index,
			unsigned short is_aff)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if ((heap_args = take_argument(map, codage, proc, op_index, 0))	== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);

	if (is_aff == 1)
		ft_printf("aff is "YEL"%u"RC, arg[0]);
	shift_pc(codage, proc, op_index);
}
