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

int		sti(unsigned char *map, t_proc *proc, unsigned short opcode)
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
		if (codage == T_REG)
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

int		ldi(unsigned char *map, t_proc *proc, unsigned short opcode)
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
		if (j != 2)
			arg[j] = proc->regs[arg[j]];
		++j;
	}
	proc->pc = (proc->pc + (arg[0] + arg[1]) % IDX_MOD) % MEM_SIZE;
	i = map[proc->pc++];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	i = (i << 8) | (unsigned int)map[proc->pc++ % MEM_SIZE];
	proc->regs[arg[0]] = (unsigned int)i;
	proc->inst_cycle = 0;
	return (1);
}