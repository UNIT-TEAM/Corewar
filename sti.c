#include "corewar.h"

t_op    op_tab[17] =
		{
				{"live", 1, {T_DIR}, 1, 10, 0, 0},
				{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
				{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
				{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
				{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
				{"and", 3,
							{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 0},
				{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
						7, 6, 1, 0},
				{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
						8, 6, 1, 0},
				{"zjmp", 1, {T_DIR}, 9, 20, 0, 1},
				{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},

				{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},

				{"fork", 1, {T_DIR}, 12, 800, 0, 1},
				{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
				{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
						14, 50, 1, 1},
				{"lfork", 1, {T_DIR}, 15, 1000, 0, 1},
				{"aff", 1, {T_REG}, 16, 2, 1, 0},
				{0, 0, {0}, 0, 0, 0, 0}
		};

int		take_arg_reg(unsigned char *map, unsigned int *arg, t_proc *proc)
{
	unsigned char index;

	index = map[0];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = proc->regs[index];
	return (1);
}

int		take_arg_dir(unsigned char *map, unsigned int *arg, t_proc *proc)
{

}

int		take_arg_ind(unsigned char *map, unsigned int *arg, t_proc *proc)
{

}

int		take_argument(unsigned char *map, const unsigned char arg_code, unsigned int *arg, t_proc *proc)
{
	if (arg_code == REG_CODE)
		return (take_arg_reg(map, arg, proc));
	else if (arg_code == DIR_CODE)
		return (take_arg_dir(map, arg, proc));
	else if (arg_code == IND_CODE)
		return (take_arg_ind(map, arg, proc));
	return (0);
}

int		check_codage(unsigned char *map, unsigned char codage, t_proc *proc,
						unsigned short opcode)
{
    unsigned char tmp;
	int i;
	int j;

	i = 8;
	j = op_tab[opcode].count_arg;
//	01 10 10 00
	while (--j >= 0)
	{
		i -= 2;
		//кожен раз зсовуємо, щоб виділити розряди для порівняння:
		//00 00 00 01, потім 00 00 00 10, 00 00 00 10
		tmp = (codage >> i) & 0x3; // & 00000011
//		виділяємо розряд в аргументі який відповідає за тип аргументу
// 		(T_REG, T_DIR, T_IND), буде 0 або 1, тобто 00000101-> 00000100
//		(для кожної команди різне) і прирівнюємо його до числа типу (001, 010, 100)
//		якшо рівні, то ок, в команді в j-му аргументі є такий тип, який закодований
//		в бінарному коді, якщо ні, то помилка.
		if (tmp == REG_CODE && ((op_tab[opcode].arg[j] & T_REG) == T_REG))
			;
		else if (tmp == DIR_CODE && ((op_tab[opcode].arg[j] & T_REG) == T_REG))
			;
		else if (tmp == IND_CODE && ((op_tab[opcode].arg[j] & T_REG) == T_REG))
			;
		else
			return (0);
	}
	//перевіряємо на нуль останні розряди (4 - count_arg)
	j = 4 - op_tab[opcode].count_arg;
	while (j > 0)
	{
		i -= 2;
		tmp = (codage >> i) & 0x3;
		if (tmp != 0)
			return (0);
	}
	return (1);
}

void	sti(unsigned char *map, t_proc *proc)
{
	unsigned int arg[3];

//	TODO доробити основу
}

//TODO написати функцію яка буде:
//1) Перевіряти на валідність opcode
//2) Викликати check_codage
//3) Викликати саму команду в залежності від opcode