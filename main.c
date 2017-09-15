#include "corewar.h"


void	base_to_zero(t_bs *bs)
{
	int i;

	bs->list_champs = NULL;
	i = -1;
	while (++i < MEM_SIZE)
		bs->map[i] = 0;
	bs->np = 0;
	bs->pftr = 0;
	bs->is_dump = 0;
	g_count = 0;
}

int		check_num_atoi(char *line, unsigned int *num)
{
	int		count;

	*num = 0;
	while (*line == '0')
		line++;
	count = 0;
	while (count <= 10 && line[count])
		count++;
	if (count > 10)
		return (0);
	if (count == 10 && ft_strncmp(line, "4294967295", 10) > 0)
		return (0);
	while (count > 0)
	{
		*num = (*num * 10) + (*line - '0');
		count--;
		line++;
	}

	return (1);
}

/*
**	i flags for error
**	1 - usage;
** 	2 - error in max players;
**	3 - error for magic;
**	4 - error when size of code is 0;
**	5 - error in malloc;
**	6 - number of player is doesnt digit
**	7 - number of cycles is doesnt digit
*/

void	ft_error(int i, char *str)
{
	if (i == 1)
		//printf(RED"Usage:"RC"\n\t./corewar [-dump nbr_cycles] [[-n number] "\
		"champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
        printf("usage");
	else if (i == 2)
		perror("error");
	else if (i == 3)
		//printf(RED"Error:"RC" File "BLU"%s"RC" has an invalid magic name\n",str);
        printf("error");
	else if (i == 4)
		//printf(RED"Error:"RC" File "BLU"%s"RC" has a code size that differ"\
		"from what its header says\n", str);
        printf("error");
	else if (i == 5)
		//printf(RED"Error:"RC" in malloc\n");
        printf("error");
	else if (i == 6)
		//printf(RED"Usage:"RC"\n\t./corewar [-dump nbr_cycles] ["RED\
		"[-n number]"RC" champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
        printf("error");
	else if (i == 7)
		//printf(RED"Usage:"RC"\n\t./corewar "RED"[-dump nbr_cycles]"RC\
		" [[-n number] champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
        printf("error");
	else if (i == 8)
		//printf(RED"Error:"BLU" %s"RC" is not unsigned int\n",str);
    printf("error");
	//видалити всі лісти
	exit(1);
}

int		parse_flags(char *flag, char *number, unsigned int *num_player,
					   unsigned int *count)
{
	int i;

	if (ft_strequ(flag, "-n"))
	{
		i = -1;
		while (number[++i])
			if (!ft_isdigit(number[i]))
				ft_error(6, number);
		if (!check_num_atoi(number, num_player))
			ft_error(8, "number");
		return (1);
	}
	else if (ft_strequ(flag, "-dump"))
	{
		i = -1;
		while (number[++i])
			if (!ft_isdigit(number[i]))
				ft_error(7, number);
		if (!check_num_atoi(number, count))
			ft_error(8, "nbr_cycles");
		return (1);
	}
	return (0);
}

void	ft_sprint(t_bs *base, char **av, int ac)
{
	int				i;
	unsigned int	num_player;

	i = 1;
	num_player = 0;
	while (i < ac)
	{
		if (i + 1 < ac - 1 &&
			parse_flags(av[i], av[i + 1], &num_player, &base->dump))
		{
			if ((i += 2) == ac && base->np == 0)
            {
                ft_error(1, NULL);
            }
			else
            {
                continue;
            }

		}
		//TODO num_player доробити
		//TODO is_dump кудись прикрутити
//		перевірку на i + 1, перед тим як передавати в парсинг
		add_new_champ(&base->list_champs, num_player);
        printf("av = %s", av[i]);
		ft_magic_size(av[i], &base->list_champs->head);
		ft_name_comment(av[i], &base->list_champs->head, 0);
		ft_name_comment(av[i], &base->list_champs->head, 1);
		ft_instraction(av[i], base);
		i++;
		num_player = 0;
	}
	//printf(YEL"Introducing contestants...\n"RC);
    printf("introducting");
	/*i = 0;
	while (++i < ac)
		printf("\t* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				  i, base->p[i - 1].prog_size, base->p[i - 1].prog_name,
				  base->p[i - 1].comment);
*/
//	ft_code();
}

int 	main(int argc, char **argv)
{
	t_bs		base;

    printf("err = %d\n", argc);
	if (argc == 1)
		ft_error(1, NULL);
	base_to_zero(&base);
	ft_sprint(&base, argv, argc);
	ft_fill_map(&base);
	//printf("sum = %d\n", 2089 % 4);
	print_map(base);
    printf("\n");
	while(base.list_champs)
	{
		printf("%u\n",base.list_champs->proc_1->pc);
		base.list_champs = base.list_champs->next;
	}
	return 0;
}
//
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
printf("s = %X\n", buf[i]);
printf("sum = %u\n", s);
return 0;

*/