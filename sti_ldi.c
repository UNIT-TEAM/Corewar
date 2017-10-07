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

int		get_all_args(unsigned char *map, t_proc *proc,
						unsigned char *opcode_codage, unsigned int *arg)
{
	unsigned char arg_code_size_flag[2];
	int i;
	int j;

	i = 8;
	j = 0;
	while (j < op_tab[opcode_codage[0] - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((opcode_codage[1] >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode_codage[0] - 1].dir_size;
		if (!take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		++j;
	}
	return (1);
}

int		sti(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char opcode_codage[2];

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);

	opcode_codage[0] = (char)opcode;
	opcode_codage[1] = codage;
	if (get_all_args(map, proc, opcode_codage, arg) == 0)
		//TODO реакція на провалену перевірку take_arg
		return (0);

	map += (arg[1] + arg[2]) % IDX_MOD;
	*((unsigned int *)map) = proc->regs[arg[0]];
	proc->inst_cycle = 0;
	return (1);
}

int		ldi(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char codage;
	unsigned char opcode_codage[2];

	if (for_instruct(map, proc, opcode, &codage) == 0)
		//TODO реакція на провалену перевірку codage
		return (0);

	opcode_codage[0] = (char)opcode;
	opcode_codage[1] = codage;
	if (get_all_args(map, proc, opcode_codage, arg) == 0)
		//TODO реакція на провалену перевірку take_arg
		return (0);

	map += (arg[0] + arg[1]) % IDX_MOD;
	proc->regs[arg[0]] = *((unsigned int *)map);
	proc->inst_cycle = 0;
	return (1);
}