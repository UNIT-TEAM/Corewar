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


void	encode_codage(unsigned char codage)
{
	unsigned char a1;

	a1 = codage & (unsigned char)0xC0; // 01
	a1 >>= 6;
	//if (op_tab[10].arg[0] == a1)
	//	return;
	if (op_tab[10].arg[1] == 0x02)
		return;
}

void	sti(unsigned char *map, t_proc *proc)
{
	encode_codage(0x68);
}

//11
//10
//01
//
//01 10 10 00