#include "corewar.h"

int		for_instruct(unsigned char *map, t_proc *proc, unsigned short op_index,
						unsigned char *codage)
{
	if (++proc->inst_cycle != op_tab[op_index].cycles)
		return (0);
	*codage = map[(proc->pc + 1) % MEM_SIZE];
	if (op_tab[op_index].codage && !check_codage(*codage, op_index))
		return (0);
	return (1);
}

int		ft_st_sti(unsigned char *map, t_proc *proc, unsigned short op_index,
				  unsigned short f_index)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;
	unsigned int tmp_pc[2];

	if (for_instruct(map, proc, op_index, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	tmp_pc[0] = (proc->pc + 2) % MEM_SIZE;
	tmp_pc[1] = proc->pc;
	while (j < op_tab[op_index].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[op_index].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, tmp_pc))
			return (0);
		if (arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	i = proc->pc + (arg[1] + (f_index) ? arg[2] : 0) % IDX_MOD;
	map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 24);
	map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 16);
	map[i++ % MEM_SIZE] = (unsigned char)(arg[0] >> 8);
	map[i % MEM_SIZE] = (unsigned char)arg[0];
	proc->pc = tmp_pc[0];
	proc->inst_cycle = 0;
	print_map(map);
	return (1);
}

int		ft_ldi_lldi(unsigned char *map, t_proc *proc, unsigned short op_index,
					   unsigned short f_long)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;
	unsigned int tmp_pc[2];

	if (for_instruct(map, proc, op_index, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	print_map(map);
	tmp_pc[0] = (proc->pc + 2) % MEM_SIZE;
	tmp_pc[1] = proc->pc;
	while (j < op_tab[op_index].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[op_index].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, tmp_pc))
			return (0);
		if (j != 2 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	j = (proc->pc + (f_long) ? (arg[0] + arg[1]) % IDX_MOD : arg[0] + arg[1]) %
			MEM_SIZE;
	i = map[j++];
	i = (i << 8) | (unsigned int)map[j++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[j++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[j % MEM_SIZE];
	proc->regs[arg[2]] = (unsigned int)i;
	proc->pc = tmp_pc[0];
	proc->inst_cycle = 0;
	if (f_long)
		proc->carry = (unsigned char)((proc->regs[arg[1]] == 0) ? 1 : 0);
	return (1);
}

int		ft_ld_lld(unsigned char *map, t_proc *proc, unsigned short op_index,
					 unsigned short f_long)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;
	unsigned int tmp_pc[2];

	if (for_instruct(map, proc, op_index, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	print_map(map);
	tmp_pc[0] = (proc->pc + 2) % MEM_SIZE;
	tmp_pc[1] = proc->pc;
	while (j < op_tab[op_index].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[op_index].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, tmp_pc))
			return (0);
		if (j != 1 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	j = (proc->pc + (f_long) ? arg[0] % IDX_MOD : arg[0]) % MEM_SIZE;
	i = map[j++];
	i = (i << 8) | (unsigned int)map[j++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[j++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[j % MEM_SIZE];
	proc->regs[arg[1]] = (unsigned int)i;
	proc->pc = tmp_pc[0];
	proc->inst_cycle = 0;
	proc->carry = (unsigned char)((proc->regs[arg[1]] == 0) ? 1 : 0);
	return (1);
}

int		ft_zjump(unsigned char *map, t_proc *proc, unsigned short op_index)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	unsigned int tmp_pc[2];

	if (!proc->carry)
		return (0);
	if (for_instruct(map, proc, op_index, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	tmp_pc[0] = (proc->pc + 1) % MEM_SIZE;
	tmp_pc[1] = proc->pc;
	arg_code_size_flag[0] = (unsigned char)((codage >> 6) & 0x3);
	arg_code_size_flag[1] = op_tab[op_index].dir_size;
	if (!take_argument(map, arg_code_size_flag, arg, tmp_pc))
		return (0);
	proc->pc = (proc->pc + (arg[0] % IDX_MOD)) % MEM_SIZE;
	proc->inst_cycle = 0;
	return (1);
}

int		ft_fork(unsigned char *map, t_proc **procs, t_proc *tmp,
				   unsigned short op_index)
{
	unsigned int arg[3];
	unsigned char arg_code_size_flag[2];
	t_proc *new_proc;
	int i;
	unsigned int tmp_pc[2];

	if (++tmp->inst_cycle != op_tab[op_index].cycles)
		return (0);
	print_map(map);
	tmp_pc[0] = (tmp->pc + 1) % MEM_SIZE;
	tmp_pc[1] = tmp->pc;
	arg_code_size_flag[0] = DIR_CODE;
	arg_code_size_flag[1] = op_tab[op_index].dir_size;
	if (!take_argument(map, arg_code_size_flag, arg, tmp_pc))
		return (0);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp->inst_cycle = 0;
	new_proc->pc = (tmp->pc + arg[0] % IDX_MOD) % MEM_SIZE;
	i = -1;
	while (++i < REG_NUMBER)
		new_proc->regs[i] = tmp->regs[i];
	new_proc->carry = tmp->carry;
	new_proc->cycle_to_die = tmp->cycle_to_die;
	new_proc->inst_cycle = tmp->inst_cycle;
	new_proc->next = *procs;
	*procs = new_proc;
	return (1);
}

int		ft_lfork(unsigned char *map, t_proc **procs, t_proc *tmp,
				   unsigned short op_index)
{
	unsigned int arg[3];
	unsigned char arg_code_size_flag[2];
	t_proc *new_proc;
	int i;
	unsigned int tmp_pc[2];

	if (++tmp->inst_cycle != op_tab[op_index].cycles)
		return (0);
	print_map(map);
	tmp_pc[0] = (tmp->pc + 1) % MEM_SIZE;
	tmp_pc[1] = tmp->pc;
	arg_code_size_flag[0] = DIR_CODE;
	arg_code_size_flag[1] = op_tab[op_index].dir_size;
	if (!take_argument(map, arg_code_size_flag, arg, tmp_pc))
		return (0);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp->inst_cycle = 0;
	new_proc->pc = (tmp->pc + arg[0] % IDX_MOD) % MEM_SIZE;
	i = -1;
	while (++i < REG_NUMBER)
		new_proc->regs[i] = tmp->regs[i];
	new_proc->carry = tmp->carry;
	new_proc->cycle_to_die = tmp->cycle_to_die;
	new_proc->inst_cycle = tmp->inst_cycle;
	new_proc->next = *procs;
	*procs = new_proc;
	return (1);
}