#include "corewar.h"

void	base_to_zero(t_bs *bs)
{
	int i;

	bs->list_champs = NULL;
	bs->list_proc = NULL;
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
		ft_printf(RED"Usage:"RC"\n\t./corewar [-dump nbr_cycles] [[-n number] "\
		"champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
	else if (i == 2)
		perror("error");
	else if (i == 3)
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has an invalid magic name\n",
				  str);
	else if (i == 4)
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has a code size that differ"\
		"from what its header says\n", str);
	else if (i == 5)
		ft_printf(RED"Error:"RC" in malloc\n");
	else if (i == 6)
		ft_printf(RED"Usage:"RC"\n\t./corewar [-dump nbr_cycles] ["RED\
		"[-n number]"RC" champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
	else if (i == 7)
		ft_printf(RED"Usage:"RC"\n\t./corewar "RED"[-dump nbr_cycles]"RC\
		" [[-n number] champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
	else if (i == 8)
		ft_printf(RED"Error:"BLU" %s"RC" is not unsigned int\n",
				  str);
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
				ft_error(1, NULL);
			else
				continue ;
		}
		//TODO num_player доробити
//		перевірку на i + 1, перед тим як передавати в парсинг
		add_new_champ(&base->list_champs, num_player, &base->list_proc);
		ft_magic_size(av[i], &base->list_champs->head);
		ft_name_comment(av[i], &base->list_champs->head, 0);
		ft_name_comment(av[i], &base->list_champs->head, 1);
		ft_instraction(av[i], base);
		i++;
		num_player = 0;
	}
	ft_printf(YEL"Introducing contestants...\n"RC);
	/*i = 0;
	while (++i < ac)
		ft_printf("\t* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				  i, base->p[i - 1].prog_size, base->p[i - 1].prog_name,
				  base->p[i - 1].comment);
*/
//	ft_code();
}

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

unsigned int g_count;

// TODO: перевірка на коректність CAPS
int 	main(int argc, char **argv)
{
	t_bs		base;

	if (argc == 1)
		ft_error(1, NULL);
	base_to_zero(&base);
	ft_sprint(&base, argv, argc);
	ft_fill_map(&base);
	while(base.list_champs)
	{
		ft_printf("%u\n",base.list_proc->pc);
		base.list_champs = base.list_champs->next;
	}
	return (0);
}