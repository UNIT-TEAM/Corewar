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

int		take_reg(unsigned char *map, unsigned int *arg, t_proc *proc)
{
	unsigned char index;

	index = map[0];
	if (index < 1 || index > REG_NUMBER)
		return (0);
	*arg = proc->regs[index];
	return (1);
}

int		take_ind()
{

}

int		take_dir()
{

}

void	encode_codage(unsigned char *map, unsigned char codage, t_proc *proc)
{

}

/*
 * 	b = 2bites
 *  if (b == (op_tab[command_index].arg[0] & 1))
 *	001
 *	010
 *	100
 *
 *	01
 *	10
 *	11
 */

void	sti(unsigned char *map, t_proc *proc)
{
	unsigned int arg[3];
	unsigned int i;
	unsigned char tmp;

	i = 0;
	//01 10 10 00
	if ((map[0] << 6) != 0)
		return ;
	tmp = map[0] >> 6;
	if (tmp != T_REG || !take_reg(map, arg, proc))
		return ;
	tmp = map[0] << 2;
	tmp >>= 6;
	if (tmp == T_REG)
	{
		if (!take_reg(map, arg, proc))
			return ;
	}
	else if (tmp == T_DIR)
	{

	}
	else if (tmp == T_IND)
	{
	}
	else
		return ;

	tmp = map[0] << 4;
	tmp >>= 6;
	if (tmp == T_DIR)
	{

	}
	else if (tmp == T_REG)
	{

	}
	else
		return ;

	//encode_codage(map, , proc);
}

//11
//10
//01
//
//01 10 10 00