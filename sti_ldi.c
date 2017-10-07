//
// Created by Dmytro Dovzhik on 10/7/17.
//

#include "corewar.h"

int		for_instruct(unsigned char *map, t_proc *proc, unsigned short opcode,
						unsigned char *codage)
{
	if (++proc->inst_cycle != op_tab[opcode - 1].cycles)
		return (0);
	print_map(map);
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	*codage = map[proc->pc];
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	if (op_tab[opcode - 1].codage && !check_codage(*codage, opcode))
		return (0);
	return (1);
}

int		ft_sti(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		if (arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc += (arg[1] + arg[2]) % IDX_MOD;
	map[proc->pc++ % MEM_SIZE] = (unsigned char)((arg[0] >> 6) & 0x3);
	// перевірити на відповідність big endian i little endian
	map[proc->pc++ % MEM_SIZE] = (unsigned char)((arg[0] >> 4) & 0x3);
	map[proc->pc++ % MEM_SIZE] = (unsigned char)((arg[0] >> 2) & 0x3);
	map[proc->pc++ % MEM_SIZE] = (unsigned char)(arg[0] & 0x3);
	proc->inst_cycle = 0;
	return (1);
}

int		ft_ldi(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		if (j != 2 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc = (proc->pc + (arg[0] + arg[1]) % IDX_MOD) % MEM_SIZE;
	i = map[proc->pc++];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	proc->regs[arg[2]] = (unsigned int)i;
	proc->inst_cycle = 0;
	return (1);
}

int		ft_ld(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		if (j == 0 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc = (proc->pc + arg[0] % IDX_MOD) % MEM_SIZE;
	//TODO CARRY!!!
	i = map[proc->pc++];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	proc->regs[arg[2]] = (unsigned int)i;
	proc->inst_cycle = 0;
	return (1);
}

int		ft_lldi(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		if (j != 2 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc = (proc->pc + arg[0] + arg[1]) % MEM_SIZE;
	//TODO CARRY
	i = map[proc->pc++];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	proc->regs[arg[2]] = (unsigned int)i;
	proc->inst_cycle = 0;
	return (1);
}

int		ft_lld(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		if (j == 0 && arg_code_size_flag[0] == REG_CODE)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc = (proc->pc + arg[0]) % MEM_SIZE;
	//TODO CARRY!!!
	i = map[proc->pc++];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	proc->regs[arg[2]] = (unsigned int)i;
	proc->inst_cycle = 0;
	return (1);
}
// TODO
// TODO
// TODO
// TODO	ГЛЯНУТЬ НА ВІДРАХУНОК ДЛЯ PC (від опкода чи кінця аргументів)
// TODO
// TODO
// TODO
// TODO
int		ft_fork(unsigned char *map, t_proc **procs, t_proc *tmp,
				   unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char arg_code_size_flag[2];
	t_proc *new_proc;
	int i;

	if (++tmp->inst_cycle != op_tab[opcode - 1].cycles)
		return (0);
	print_map(map);
	tmp->pc = (tmp->pc + 1) % MEM_SIZE;
	arg_code_size_flag[0] = DIR_CODE;
	arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
	if (!take_argument(map, arg_code_size_flag, arg, tmp))
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
				   unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char arg_code_size_flag[2];
	t_proc *new_proc;
	int i;

	if (++tmp->inst_cycle != op_tab[opcode - 1].cycles)
		return (0);
	print_map(map);
	tmp->pc = (tmp->pc + 1) % MEM_SIZE;
	arg_code_size_flag[0] = DIR_CODE;
	arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
	if (!take_argument(map, arg_code_size_flag, arg, tmp))
		return (0);
	if (!(new_proc = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, NULL);
	tmp->inst_cycle = 0;
	new_proc->pc = (tmp->pc + arg[0]) % MEM_SIZE;
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