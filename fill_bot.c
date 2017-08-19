#include "corewar.h"

void	ft_magic(unsigned int magic, char *read, char *str)
{
	unsigned int arr[4];

	arr[0] = (unsigned int)(read[0] << 24);
	arr[1] = (unsigned int)(read[1] << 16 & 0x00ffffff);
	arr[2] = (unsigned int)(read[2] << 8 & 0x0000ffff);
	arr[3] = (unsigned int)(read[3] & 0x000000ff);
	if ((magic = arr[0] | arr[1] | arr[2] | arr[3]) == COREWAR_EXEC_MAGIC)
		return ;
	else
	{
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has an invalid magic name\n",\
		str);
		exit(1);
	}
}

void	ft_name(char *str)
{
	 
}