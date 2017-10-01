#include "corewar.h"

/*
 * TODO: зробити перевірку на розмір REG, DIR, IND
 */



int		take_arg_reg(unsigned char *map, unsigned int *arg, t_proc *proc)
{
	unsigned char index;

	index = map[proc->pc];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = proc->regs[index - 1];
	return (1);
}

int		take_arg_dir(unsigned char *map, unsigned int *arg, t_proc *proc,
						unsigned char flag_size)
{
	unsigned char code[4];

	if (flag_size == 0)
	{
		code[0] = map[proc->pc];
		code[1] = map[(proc->pc + 1) % MEM_SIZE];
		code[2] = map[(proc->pc + 2) % MEM_SIZE];
		code[3] = map[(proc->pc + 3) % MEM_SIZE];
		*arg = *((unsigned int *)code);
	}
	else
	{
		code[0] = map[proc->pc];
		code[1] = map[(proc->pc + 1) % MEM_SIZE];
		*arg = *((unsigned short *)code);
	}
	return (1);
}

int		take_arg_ind(unsigned char *map, unsigned int *arg, t_proc *proc)
{
	unsigned char code[2];
	unsigned short p;


	code[0] = map[proc->pc];
	code[1] = map[(proc->pc + 1) % MEM_SIZE];
	p = (unsigned short)(*((unsigned short *)code) % MEM_SIZE);
	code[0] = map[p];
	code[1] = map[(p + 1) % MEM_SIZE];
	*arg = *((unsigned short *)code);
	return (1);
}

int		take_argument(unsigned char *map, unsigned char *arg_code_size_flag,
						 unsigned int *arg, t_proc *proc)
{
	if (arg_code_size_flag[0] == REG_CODE)
	{
		proc->pc += REG_SIZE;
		return (take_arg_reg(map, arg, proc));
	}
	else if (arg_code_size_flag[0] == DIR_CODE)
	{
		proc->pc += DIR_SIZE;
		return (take_arg_dir(map, arg, proc, arg_code_size_flag[1]));
	}
	else if (arg_code_size_flag[0] == IND_CODE)
	{
		proc->pc += IND_SIZE;
		return (take_arg_ind(map, arg, proc));
	}
	return (0);
}

int		check_codage(unsigned char codage, unsigned short opcode)
{
    unsigned char tmp;
	int i;
	int j;

	i = 8;
	j = 0;
//	01 10 10 00
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2; //00000111
		//кожен раз зсовуємо, щоб виділити розряди для порівняння:
		//00 00 00 01, потім 00 00 00 10, 00 00 00 10
		tmp = (unsigned char)((codage >> i) & 0x3); // & 00000011
//		виділяємо розряд в аргументі який відповідає за тип аргументу
// 		(T_REG, T_DIR, T_IND), буде 0 або 1, тобто 00000101-> 00000100
//		(для кожної команди різне) і прирівнюємо його до числа типу (001, 010, 100)
//		якшо рівні, то ок, в команді в j-му аргументі є такий тип, який закодований
//		в бінарному коді, якщо ні, то помилка. //00000001 & 00000001 == 00000001
		if (tmp == REG_CODE && ((op_tab[opcode - 1].arg[j] & T_REG) == T_REG))
			;
		else if (tmp == DIR_CODE && ((op_tab[opcode - 1].arg[j] & T_DIR) == T_DIR))
			;
		else if (tmp == IND_CODE && ((op_tab[opcode - 1].arg[j] & T_IND) == T_IND))
			;
		else
			return (0);
		++j;
	}
	//перевіряємо на нуль останні розряди (4 - count_arg)
	j = 4 - op_tab[opcode].count_arg;
	while (j > 0)
	{
		i -= 2;
		tmp = (unsigned char)((codage >> i) & 0x3);
		if (tmp != 0x0)
			return (0);
		--j;
	}
	return (1);
}

int		sti(unsigned char *map, t_proc *proc, unsigned short opcode)
{
	unsigned int arg[3];
	unsigned char arg_code_size_flag[2];
	unsigned char codage;
	int i;
	int j;

	codage = map[(proc->pc + 1) % MEM_SIZE];
	if (!check_codage(codage, opcode))
		return (0);
	map -= proc->pc;
	i = 8;
	j = 0;
	while (j < op_tab[opcode - 1].count_arg)
	{
		i -= 2;
		arg_code_size_flag[0] = (unsigned char)((codage >> i) & 0x3);
		arg_code_size_flag[1] = op_tab[opcode - 1].dir_size;
		if (take_argument(map, arg_code_size_flag, arg + j, proc))
			return (0);
		++j;
	}
	map += (arg[1] + arg[2]) % IDX_MOD;
	*((unsigned int *)map) = arg[0];
	return (1);
}