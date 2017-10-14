#include "corewar.h"

int		take_arg_reg(unsigned char *map, unsigned int *arg, unsigned int *tmp_pc)
{
	unsigned char index;

	index = map[*tmp_pc];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = (unsigned int)(index - 1);
	return (1);
}

int		take_arg_dir(unsigned char *map, unsigned int *arg, unsigned int *tmp_pc,
						unsigned char flag_size)
{
	unsigned char code[4];
	unsigned int p;

	if (flag_size == 0)
	{
		code[0] = map[(tmp_pc[0] + 3) % MEM_SIZE];
		code[1] = map[(tmp_pc[0] + 2) % MEM_SIZE];
		code[2] = map[(tmp_pc[0] + 1) % MEM_SIZE];
		code[3] = map[tmp_pc[0]];
		p = *((unsigned int *)code) % MEM_SIZE;
	}
	else
	{
		code[0] = map[(tmp_pc[0] + 1) % MEM_SIZE];
		code[1] = map[tmp_pc[0]];
		p = (unsigned short)(*((unsigned short *)code) % MEM_SIZE);
	}
	code[0] = map[(tmp_pc[1] + p + 3) % MEM_SIZE];
	code[1] = map[(tmp_pc[1] + p + 2) % MEM_SIZE];
	code[2] = map[(tmp_pc[1] + p + 1) % MEM_SIZE];
	code[3] = map[(tmp_pc[1] + p) % MEM_SIZE];
	*arg = *((unsigned int *)code);
	return (1);
}

int		take_arg_ind(unsigned char *map, unsigned int *arg, unsigned int *tmp_pc)
{
	unsigned char code[2];

	code[0] = map[(*tmp_pc + 1) % MEM_SIZE];
	code[1] = map[*tmp_pc];
	*arg = *((unsigned short *)code);
	return (1);
}

int		take_argument(unsigned char *map, unsigned char *arg_code_size_flag,
							 unsigned int *arg, unsigned int *tmp_pc)
{
	int res;

	res = 0;
	if (arg_code_size_flag[0] == REG_CODE)
	{
		res = take_arg_reg(map, arg, tmp_pc);
		*tmp_pc = (*tmp_pc + 1) % MEM_SIZE;
	}
	else if (arg_code_size_flag[0] == DIR_CODE)
	{
		res = take_arg_dir(map, arg, tmp_pc, arg_code_size_flag[1]);
		*tmp_pc = (*tmp_pc + ((arg_code_size_flag[1] == 1) ? 2 : 4)) % MEM_SIZE;
	}
	else if (arg_code_size_flag[0] == IND_CODE)
	{
		res = take_arg_ind(map, arg, tmp_pc);
		*tmp_pc = (*tmp_pc + IND_SIZE) % MEM_SIZE;
	}
	return (res);
}

void	shift_pc(unsigned char codage, t_proc *proc, unsigned short index)
{
	unsigned char tmp;
	int i;
	int j;

	i = 8;
	j = 0;
	while (j < op_tab[index].count_arg)
	{
		i -= 2;
		tmp = (unsigned char)((codage >> i) & 0x3);
		if (tmp == REG_CODE)
			proc->pc += 1;
		else if (tmp == DIR_CODE)
			proc->pc += (op_tab[index].dir_size) ? 2 : 4;
		else if (tmp == IND_CODE)
			proc->pc += IND_SIZE;
		++j;
	}
}

int		check_codage(unsigned char codage, t_proc *proc, unsigned short index)
{
    unsigned char tmp;
	int i;
	int j;

	i = 8;
	j = 0;
//	01 10 10 00
	while (j < op_tab[index].count_arg)
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
		if (tmp == REG_CODE && ((op_tab[index].arg[j] & T_REG) == T_REG))
			;
		else if (tmp == DIR_CODE && ((op_tab[index].arg[j] & T_DIR) == T_DIR))
			;
		else if (tmp == IND_CODE && ((op_tab[index].arg[j] & T_IND) == T_IND))
			;
		else
		{
			shift_pc(codage, proc, index);
			return (0);
		}
		++j;
	}
	return (1);
}