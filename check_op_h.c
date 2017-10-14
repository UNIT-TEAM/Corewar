#include "corewar.h"

int	check_op_h()
{
	if (MAX_PLAYERS > 4 || MAX_PLAYERS <= 0)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect MAX_PLAERS\n"RC);
		return (0);
	}
	//TODO можливо більш мякішу перевірку зробити
	if (MEM_SIZE != 4096)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect MEM_SIZE\n"RC);
		return (0);
	}
	if (IDX_MOD != 512)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect IDX_MOD\n"RC);
		return (0);
	}
	if (CHAMP_MAX_SIZE != 682)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect CHAMP_MAX_SIZE\n"RC);
		return (0);
	}
	if (T_REG != 1)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect T_REG\n"RC);
		return (0);
	}
	if (T_DIR != 2)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect T_DIR_\n"RC);
		return (0);
	}
	if (T_IND != 4)
	{
		ft_printf(RED"Error:"RC"\n\t\t"BLU"Incorrect T_IND\n"RC);
		return (0);
	}
	return (1);
}