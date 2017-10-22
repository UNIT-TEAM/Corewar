#include "corewar.h"

int		take_arg_reg(unsigned char *map, unsigned int *arg, unsigned int *tmp_pc)
{
	unsigned char index;

	index = map[*tmp_pc];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = (unsigned int)(index - 1);
	*tmp_pc = (*tmp_pc + 1) % MEM_SIZE;
	return (1);
}

int		take_arg_dir(unsigned char *map, unsigned int *arg, unsigned int *tmp_pc,
						unsigned short op_index)
{
	unsigned char code[4];

	if (op_tab[op_index].dir_size == 0)
	{
		code[0] = map[(*tmp_pc + 3) % MEM_SIZE];
		code[1] = map[(*tmp_pc + 2) % MEM_SIZE];
		code[2] = map[(*tmp_pc + 1) % MEM_SIZE];
		code[3] = map[*tmp_pc];
		*arg = *((unsigned int *)code);
		*tmp_pc = (*tmp_pc + 4) % MEM_SIZE;
	}
	else
	{
		code[0] = map[(*tmp_pc + 1) % MEM_SIZE];
		code[1] = map[*tmp_pc];
		*arg = *((unsigned short *)code);
		*tmp_pc = (*tmp_pc + 2) % MEM_SIZE;
	}
	return (1);
}

unsigned int	take_value_from_addres(unsigned char *map, t_proc *proc,
									   short address, short flag_long)
{
	unsigned int index;
	unsigned int value;

	if (flag_long == 0)
		index = (unsigned int)((long)proc->pc + address % IDX_MOD < 0 ?
							   MEM_SIZE +
							((long)proc->pc + address % IDX_MOD) % MEM_SIZE :
				 			((long)proc->pc + address % IDX_MOD) % MEM_SIZE);
	else
		index = (unsigned int)((long)proc->pc + address < 0 ?
							   MEM_SIZE +
									   ((long)proc->pc + address) % MEM_SIZE :
							   ((long)proc->pc + address) % MEM_SIZE);
	value = map[index++ % MEM_SIZE];
	value = (value << 8) | (unsigned int) map[index++ % MEM_SIZE];
	value = (value << 8) | (unsigned int) map[index++ % MEM_SIZE];
	value = (value << 8) | (unsigned int) map[index % MEM_SIZE];
	return (value);
}

int		take_arg_ind(unsigned char *map, unsigned int *arg,
						unsigned int *tmp_pc, t_proc *proc, short flag_long)
{
	unsigned char code[2];
	unsigned short p;

	code[0] = map[(*tmp_pc + 1) % MEM_SIZE];
	code[1] = map[*tmp_pc];
	p = *((unsigned short *)code);
	*arg = take_value_from_addres(map, proc, p, flag_long);
	*tmp_pc = (*tmp_pc + 2) % MEM_SIZE;
	return (1);
}

unsigned int	*take_argument(unsigned char *map, unsigned char codage,
						 t_proc *proc, unsigned short op_index, short flag_long)
{
	int res;
	int i;
	int j;
	unsigned int tmp_pc;
	unsigned int *arg;

	if ((arg = (unsigned int *)malloc(
			sizeof(unsigned int) * op_tab[op_index].count_arg)) == NULL)
		ft_error(5, NULL);
	tmp_pc = (op_tab[op_index].is_codage ?
			  	proc->pc + 2 : proc->pc + 1) % MEM_SIZE;
	j = 8;
	i = -1;
	while (++i < op_tab[op_index].count_arg)
	{
		j -= 2;
		res = 0;
		if (((codage >> j) & 0x3) == REG_CODE)
			res = take_arg_reg(map, arg + i, &tmp_pc);
		else if (((codage >> j) & 0x3) == DIR_CODE)
			res = take_arg_dir(map, arg + i, &tmp_pc, op_index);
		else if (((codage >> j) & 0x3) == IND_CODE)
			res = take_arg_ind(map, arg + i, &tmp_pc, proc, flag_long);
		if (res == 0)
		{
			shift_pc(codage, proc, op_index);
			return (NULL);
		}
	}
	return (arg);
}

void	shift_pc(unsigned char codage, t_proc *proc, unsigned short op_index)
{
	unsigned char tmp;
	int i;
	int j;

	i = 8;
	j = 0;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	proc->pc = (proc->pc + (op_tab[op_index].is_codage ? 1 : 0)) % MEM_SIZE;
	while (j < op_tab[op_index].count_arg)
	{
		i -= 2;
		tmp = (unsigned char)((codage >> i) & 0x3);
		if (tmp == REG_CODE)
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		else if (tmp == DIR_CODE)
			proc->pc = (proc->pc + (op_tab[op_index].dir_size ? 2 : 4)) %
					   MEM_SIZE;
		else if (tmp == IND_CODE)
			proc->pc = (proc->pc + IND_SIZE) % MEM_SIZE;
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