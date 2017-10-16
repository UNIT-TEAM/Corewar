#include "corewar.h"

int	for_instruct(unsigned char *map, t_proc *proc, unsigned short op_index,
						unsigned char *codage)
{
	if (++proc->inst_cycle != op_tab[op_index].cycles)
		return (0);
	*codage = map[(proc->pc + 1) % MEM_SIZE];
	if (op_tab[op_index].is_codage && !check_codage(*codage, proc, op_index))
		return (0);
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

void	ft_live(unsigned char *map, t_proc *proc, unsigned short op_index,
				   t_chmp *champs)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	t_chmp *curr;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if ((heap_args = take_argument(map, codage, proc, op_index))
			== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	proc->is_live = 1;
	curr = champs;
	while (curr)
	{
		if (curr->num == arg[0])
		{
			++curr->live;
			curr->cycle_live = g_count;
		}
		curr = curr->next;
	}
	shift_pc(codage, proc, op_index);
	//print_map(map);
	ft_printf("LIVE\n");
}

void	ft_ld_lld_ldi_lldi(unsigned char *map, t_proc *proc,
						   unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	unsigned int load_value;
	int i;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	if ((heap_args = take_argument(map, codage, proc, op_index)) == NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (ft_strequ(op_tab[op_index].name, "ldi") ||
			ft_strequ(op_tab[op_index].name, "lldi"))
	{
		arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ?
				 proc->regs[arg[0]] : arg[0];
		arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ?
				 proc->regs[arg[1]] : arg[1];
	}
	if (ft_strequ(op_tab[op_index].name, "ld"))
		i = proc->pc + arg[0] % IDX_MOD;
	else if (ft_strequ(op_tab[op_index].name, "lld"))
		i = proc->pc + arg[0];
	else if (ft_strequ(op_tab[op_index].name, "ldi"))
		i = proc->pc + (arg[0] + arg[1]) % IDX_MOD;
	else if (ft_strequ(op_tab[op_index].name, "lldi"))
		i = proc->pc + arg[0] + arg[1];
	load_value = map[i++ % MEM_SIZE];
	load_value = (load_value << 8) | (unsigned int)map[i++ % MEM_SIZE];
	load_value = (load_value << 8) | (unsigned int)map[i++ % MEM_SIZE];
	load_value = (load_value << 8) | (unsigned int)map[i % MEM_SIZE];
	if (ft_strequ(op_tab[op_index].name, "ld") ||
			ft_strequ(op_tab[op_index].name, "lld"))
	{
		proc->regs[arg[1]] = load_value;
		proc->carry = (unsigned char)(proc->regs[arg[1]] == 0 ? 1 : 0);
	}
	else if (ft_strequ(op_tab[op_index].name, "ldi") ||
			 ft_strequ(op_tab[op_index].name, "lldi"))
	{
		proc->regs[arg[2]] = load_value;
		proc->carry = (unsigned char)(proc->regs[arg[2]] == 0 ? 1 : 0);
	}
	shift_pc(codage, proc, op_index);
}

void	ft_st_sti(unsigned char *map, t_proc *proc, unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;
	int i;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	if ((heap_args = take_argument(map, codage, proc, op_index))
		== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	arg[0] = (((codage >> 6) & 0x3) == REG_CODE) ?
			 proc->regs[arg[0]] : arg[0];
	arg[1] = (((codage >> 4) & 0x3) == REG_CODE) ?
			 proc->regs[arg[1]] : arg[1];
	if (ft_strequ(op_tab[op_index].name, "sti"))
		arg[2] = (((codage >> 2) & 0x3) == REG_CODE) ?
				 proc->regs[arg[2]] : arg[2];
	if (ft_strequ(op_tab[op_index].name, "st"))
		i = proc->pc + arg[1] % IDX_MOD;
	else if (ft_strequ(op_tab[op_index].name, "sti"))
		i = proc->pc + (arg[1] + arg[2]) % IDX_MOD;
	map[i++ % MEM_SIZE] = (unsigned char) (arg[0] >> 24);
	map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 16);
	map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 8);
	map[i % MEM_SIZE] = (unsigned char)arg[0];
	shift_pc(codage, proc, op_index);
	print_map(map);
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
	if ((heap_args = take_argument(map, codage, proc, op_index)) == NULL)
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
	if ((heap_args = take_argument(map, codage, proc, op_index)) == NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (proc->carry == 1)
		proc->pc = ((proc->pc + ((short)arg[0] % IDX_MOD)) + MEM_SIZE) % MEM_SIZE;
	else
		shift_pc(codage, proc, op_index);

	//print_map(map);
	ft_printf("zjump\n");
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
	if ((heap_args = take_argument(map, codage, tmp, op_index))
		== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	if (ft_strequ(op_tab[op_index].name, "fork"))
		new_proc->pc = (tmp->pc + arg[0] % IDX_MOD) % MEM_SIZE;
	else if (ft_strequ(op_tab[op_index].name, "lfork"))
		new_proc->pc = (tmp->pc + arg[0]) % MEM_SIZE;
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

void	ft_aff(unsigned char *map, t_proc *proc, unsigned short op_index)
{
	unsigned int arg[op_tab[op_index].count_arg];
	unsigned int *heap_args;
	unsigned char codage;

	if (for_instruct(map, proc, op_index, &codage) == 0)
		return ;
	proc->inst_cycle = 0;
	codage = DIR_CODE << 6;
	if ((heap_args = take_argument(map, codage, proc, op_index))
		== NULL)
		return ;
	parse_heap_to_stack_args(arg, &heap_args, op_tab[op_index].count_arg);

	//if (bs->is_aff == 0) не друкуємо а при 1 друкуємо
	ft_printf("%c", proc->regs[arg[0]]);
	shift_pc(codage, proc, op_index);
}
//TODO якщо передадуть відємне значення!!!!! треба всюди зробити (x + MEM_SIZE) % MEM_SIZE