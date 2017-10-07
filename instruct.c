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
	*arg = (unsigned int)(index - 1);
	return (1);
}

int		take_arg_dir(unsigned char *map, unsigned int *arg, t_proc *proc,
						unsigned char flag_size)
{
	unsigned char code[4];

	if (flag_size == 0)
	{
		code[0] = map[(proc->pc + 3) % MEM_SIZE];
		code[1] = map[(proc->pc + 2) % MEM_SIZE];
		code[2] = map[(proc->pc + 1) % MEM_SIZE];
		code[3] = map[proc->pc];
		*arg = *((unsigned int *)code);
	}
	else
	{
		code[0] = map[(proc->pc + 1) % MEM_SIZE];
		code[1] = map[proc->pc];
		*arg = (unsigned int)*((unsigned short *)code);
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
	int res;

	res = 0;
	if (arg_code_size_flag[0] == REG_CODE)
	{
		res = take_arg_reg(map, arg, proc);
		proc->pc = (proc->pc + 1) % MEM_SIZE;
	}
	else if (arg_code_size_flag[0] == DIR_CODE)
	{
		res = take_arg_dir(map, arg, proc, arg_code_size_flag[1]);
		proc->pc = (proc->pc + ((arg_code_size_flag[1] == 1) ? 2 : 4)) % MEM_SIZE;
	}
	else if (arg_code_size_flag[0] == IND_CODE)
	{
		res = take_arg_ind(map, arg, proc);
		proc->pc = (proc->pc + IND_SIZE) % MEM_SIZE;
	}
	return (res);
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