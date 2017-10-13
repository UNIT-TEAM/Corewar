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
	bs->is_dump = 0;
	bs->is_num_flag = 0;
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
//TODO 10 - дописати помилку про нестачу аргументів для флага -n
//TODO 11 - про n < 1 || n > MAX_CHECK для флага -n
//TODO 12 - про повторення номера у -n
void	ft_error(int i, char *str)
{
	if (i == 1)
		ft_printf(RED"Usage:"RC"\n\t./corewar [[-dump N] [-print N] [-a] [-b]]"\
		" | [[-n number] champion1.cor] | -v] \n\tMax players is %d\n\n#### T"\
		"EXT OUTPUT MODE #####################################################"\
		"#####\n\t-dump N\t\t: Dumps memory after N cycles then exits;\n\t-pri"\
		"nt N\t: Every N cycles, print dump memory;\n\t-a\t\t\t: Prints output"\
		" from \"aff\" (Default is to hide it);\n\t-b\t\t\t: Enable sound when"\
		" process is die;\n\n#### NCURSES OUTPUT MODE ########################"\
		"###############################\n\t-v\t\t\t: Ncurses output mode",\
		 MAX_PLAYERS);
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
		ft_printf(RED"Usage:"RC"\n\t./corewar "RED\
		"[-n number]"RC);
	else if (i == 7)
		ft_printf(RED"Usage:"RC"\n\t./corewar "RED"[-dump nbr_cycles]"RC\
		" [[-n number] champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
	else if (i == 8)
		ft_printf(RED"Error:"BLU" %s"RC" is not unsigned int\n", str);
	else if (i == 9)
		ft_printf(RED"Usage:"RC"\n\t./corewar "RED"[-dump nbr_cycles | -dump_go"
						  " nbr_cycles]"RC\
		" [[-n number] champion1.cor] ...\n\tMax players is %d", MAX_PLAYERS);
	//TODO видалити всі лісти
	//TODO Usage перевірити
	exit(1);
}
unsigned int	parse_flag_num(t_bs *bs, char **argv, int argc, int *index)
{
	int i;
	unsigned int num_player;

	num_player = 0;
	if (ft_strequ(argv[*index], "-n"))
	{
		i = -1;
		if (i + 2 < argc - 1)
			ft_error(10, NULL);
		while (argv[*index + 1][++i])
			if (!ft_isdigit(argv[*index + 1][i]))
				ft_error(6, argv[*index + 1]);
		if (!check_num_atoi(argv[*index + 1], &num_player))
			ft_error(8, "number");
		if (open(argv[i + 2], O_RDONLY) < 0)
			ft_error(2, NULL);
		if (num_player < 1 || num_player > MAX_CHECKS)
			ft_error(11, NULL);
		bs->is_num_flag = 1;
	}
	return (num_player);
}

//int parse_flag_dump()
//{
//	else if (ft_strequ(flag, "-dump"))
//	{
//		i = -1;
//		while (number[++i])
//			if (!ft_isdigit(number[i]))
//				ft_error(7, number);
//		if (!check_num_atoi(number, count))
//			ft_error(8, "nbr_cycles");
//		return (1);
//	}
//}
//
//int parse_flag_visual()
//{
//}

void	num_champs(t_chmp *champs)
{
	t_chmp *tmp;
	unsigned int number;

	tmp = champs;
	number = 1;
	while (tmp)
	{
		tmp->num = number++;
		tmp = tmp->next;
	}
}

void	ft_sprint(t_bs *base, char **av, int ac)
{
	int				i;
	unsigned int	num_player;

	i = 1;
	while (i < ac)
	{
		num_player = parse_flag_num(base, av, ac, &i);
		//TODO не записується гравець
		add_new_champ(&base->list_champs, num_player, &base->list_proc);
		ft_magic_size(av[i], &base->list_champs->head);
		ft_name_comment(av[i], &base->list_champs->head, 0);
		ft_name_comment(av[i], &base->list_champs->head, 1);
		ft_instraction(av[i], base);
		//		parse_flag_dump();
		//		parse_flag_visual();
		i++;
	}
	base->winner = base->list_champs->num;
	num_champs(base->list_champs);
	ft_printf(YEL"Introducing contestants...\n"RC);
}

unsigned int g_count;

// TODO: перевірка на коректність CAPS
//TODO зробити перевірку на всі зміни в хедері op.h!!!!
int 	main(int argc, char **argv)
{
	t_bs		base;

	if (argc == 1)
		ft_error(6, NULL);
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