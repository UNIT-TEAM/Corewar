
#include "corewar.h"

void	base_to_zero(t_bs *bs)
{
	int i;

	i = -1;
	bs->pftr = 0;
	while (++i < MEM_SIZE)
		bs->map[i] = 0;
}

/*
**	i flags for error
**	1 - usage;
** 	2 - error in max players;
**	3 - error for magic;
**	4 - error when size of code is 0;
*/

void ft_error(int i, char *str)
{
	if (i == 1)
		ft_printf(RED"Usage:"RC"\n\t./corewar <champion1.cor> <...>\n\t"\
		"Max players is %d", MAX_PLAYERS);
	else if (i == 2)
		perror("error");
	else if (i == 3)
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has an invalid magic name\n",
				  str);
	else if (i == 4)
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has a code size that differ"\
		"from what its header says\n", str);
	exit(1);
}

void	ft_sprint(t_bs *base, char **av, int ac)
{
	int	i;

	i = 0;
	base->np = ac - 1;
	while (++i < ac)
	{
		ft_magic_size(av[i], &base->p[i - 1]);
		ft_name_comment(av[i], &base->p[i - 1], 0);
		ft_name_comment(av[i], &base->p[i - 1], 1);
		ft_instraction(av[i], base, i - 1);
	}
	ft_printf(YEL"Introducing contestants...\n"RC);
	i = 0;
	while (++i < ac)
		ft_printf("\t* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				  i, base->p[i - 1].prog_size, base->p[i - 1].prog_name,
				  base->p[i - 1].comment);

//	ft_size(av, ac, base->p);
//	ft_code();
}

int 	main(int argc, char **argv)
{
	t_bs		base;

	if (argc == 1 || argc - 1 > MAX_PLAYERS)
		ft_error(1, NULL);
	base_to_zero(&base);
	ft_sprint(&base, argv, argc);
	ft_printf("sum = %d\n", 2089 % 4);
	return 0;
}

// зчитування імені
/*

	unsigned int	arr[4];
	unsigned int	s;
	char			buf[4];
	int 			fd;
	int 			i;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	read(fd, &buf, 4);

	arr[0] = (unsigned int)(buf[0] << 24);
	arr[1] = (unsigned int)(buf[1] << 16 & 0x00ffffff);
	arr[2] = (unsigned int)(buf[2] << 8 & 0x0000ffff);
	arr[3] = (unsigned int)(buf[3] & 0x000000ff);
	s = arr[0] | arr[1] | arr[2] | arr[3];*//*


while (++i < 4)
ft_printf("s = %X\n", buf[i]);
ft_printf("sum = %u\n", s);
return 0;

*/
