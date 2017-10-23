#include "corewar.h"

void	del_list_champ(t_chmp **champ)
{
	t_chmp *tmp;
	t_chmp *trash;

	trash = *champ;
	while (trash)
	{
		tmp = trash->next;
		free(trash->instructions);
		free(trash);
		trash = tmp;
	}
	*champ = NULL;
}

void	del_list_proc(t_proc **proc)
{
	t_proc *tmp;
	t_proc *trash;

	trash = *proc;
	while (trash)
	{
		tmp = trash->next;
		free(trash);
		trash = tmp;
	}
	*proc = NULL;
}

void	base_to_zero(t_bs *bs)
{
	int i;

	bs->list_champs = NULL;
	bs->list_proc = NULL;
	i = -1;
	while (++i < MEM_SIZE)
	{
		bs->map[i] = 0;
		bs->color_map[i].champ = 0;
		bs->color_map[i].live = 0;
	}
	bs->np = 0;
	bs->num_live = 0;
	bs->is_dump = 0;
	bs->is_print = 0;
	bs->is_visual = 0;
	bs->is_num_flag = 0;
	bs->is_aff = 0;
	bs->is_beep = 0;
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
**  8 - number is not unsigned int
**	9 - number of print cicles must be a digit
**	10
**	11 - number of player must be a 1 <= number < MAX_PLAYERS
**	12 - identical numbers
*/
void 	ft_error1(int i, char *str)
{
	if (i == 7)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-dump N]"RC" - must be a digit\n");
	else if (i == 8)
		ft_printf(RED"Error:"BLU"\n\t\t%s"RC" is not unsigned int\n", str);
	else if (i == 9)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-print N]"RC" - must be a digit\n");
	else if (i == 10)
		ft_printf(RED"Error:"BLU"\n\t\tnot enough arguments"RC"\n", str);
	else if (i == 11)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - should be in the "\
        "range 1 <= number <= MAX_PLAYER\n");
	else if (i == 12)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - identical numbers"\
        "\n");
	else if (i == 13)
		ft_printf(RED"Error:"RC"\n\t\tchamps - should be in the range 1 <= num"\
        "ber <= MAX_PLAYER\n");
	else if (i == 14)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-dump N]"RC" - must be a digit"\
        "\n");
	else if (i == 15)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-print N]"RC" - must be a digit"\
        "\n");
//TODO видалити всі лісти
	exit(1);
}

void	ft_error(int i, char *str)
{
	if (i == 1)
		ft_printf(RED"Usage:"RC"\n\t./corewar [[-dump N] [-print N] [-a] [-b]]"\
		" | [[-n number] champion1.cor] | -v] \n\tMax players is %d\n\n#### T"\
		"EXT OUTPUT MODE #####################################################"\
		"#####\n\t-dump N\t\t: Dumps memory after N cycles then exits;\n\t-pri"\
		"nt N\t: Every N cycles, print dump memory;\n\t-a\t\t\t: Prints output"\
		" from \"aff\" (Default is to hide it);\n\t-b\t\t\t: Enable sound when"\
		" process is die;\n\t-n number\t: Sets the number of the next player\n"\
		"\n#### NCURSES OUTPUT MODE ##########################################"\
		"#############\n\t-v\t\t\t: Ncurses output mode\n", MAX_PLAYERS);
	else if (i == 2)
		perror("error");
	else if (i == 3)
		ft_printf(RED"Error:"RC"\n\t\tFile "BLU"%s"RC" has an invalid magic na"\
		"me\n", str);
	else if (i == 4)
		ft_printf(RED"Error:"RC"\n\t\tFile "BLU"%s"RC" has a code size that di"\
		"ffer from what its header says\n", str);
	else if (i == 5)
		ft_printf(RED"Error:"RC"\n\t\tin malloc\n");
	else if (i == 6)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - must be a digit"\
		"\n");
	ft_error1(i, str);
}
unsigned int	parse_flag_num(t_bs *bs, char **argv, int argc, int *index)
{
	int i;
	int fd;
	unsigned int num_player;

	num_player = 0;
	if (ft_strequ(argv[*index], "-n"))
	{
		if (*index + 2 > argc - 1)
			ft_error(10, NULL);
		i = -1;
		while (argv[*index + 1][++i])
			if (!ft_isdigit(argv[*index + 1][i]))
				ft_error(6, argv[*index + 1]);
		if (!check_num_atoi(argv[*index + 1], &num_player))
			ft_error(8, argv[*index + 1]);
		if ((fd = open(argv[*index + 2], O_RDONLY)) < 0)
			ft_error(2, NULL);
		else
			close(fd);
		if (num_player < 1 || num_player > MAX_CHECKS)
			ft_error(11, NULL);
		bs->is_num_flag = 1;
		*index += 2;
	}
	return (num_player);
}

void	parse_flag_dump(t_bs *bs, char **argv, int argc, int *index)
{
	int i;
	int fd;
	unsigned int tmp;

	if (ft_strequ(argv[*index], "-dump"))
	{
		if (*index + 2 > argc - 1)
			ft_error(10, NULL);
		i = -1;
		while (argv[*index + 1][++i])
			if (!ft_isdigit(argv[*index + 1][i]))
				ft_error(12, argv[*index + 1]);
		if (!check_num_atoi(argv[*index + 1], &tmp))
			ft_error(8, argv[*index + 1]);
		if ((fd = open(argv[*index + 2], O_RDONLY)) < 0)
			ft_error(2, NULL);
		else
			close(fd);
		bs->dump = tmp;
		bs->is_dump = 1;
		*index += 2;
	}
}


void	parse_flag_print(t_bs *bs, char **argv, int argc, int *index)
{
	int i;
	unsigned int tmp;

	if (ft_strequ(argv[*index], "-print"))
	{
		if (*index + 2 > argc - 1)
			ft_error(10, NULL);
		i = -1;
		while (argv[*index + 1][++i])
			if (!ft_isdigit(argv[*index + 1][i]))
				ft_error(15, argv[*index + 1]);
		if (!check_num_atoi(argv[*index + 1], &tmp))
			ft_error(8, argv[*index + 1]);
		bs->cycle_print = tmp;
		bs->is_print = 1;
		*index += 2;
	}
}

void	parse_flag_visual_aff_beep(t_bs *bs, char **argv, int *index)
{
	if (ft_strequ(argv[*index], "-v"))
		bs->is_visual = 1;
	else if (ft_strequ(argv[*index], "-a"))
		bs->is_aff = 1;
	else if (ft_strequ(argv[*index], "-b"))
		bs->is_beep = 1;
	if (ft_strequ(argv[*index], "-v") || ft_strequ(argv[*index], "-a") ||
			ft_strequ(argv[*index], "-b"))
		*index += 1;
}

void	num_champs(t_chmp *champs, unsigned short is_visual)
{
	t_chmp *tmp;
	unsigned int number;

	tmp = champs;
	number = 1;
	if (is_visual == 0)
		ft_printf(YEL"Introducing contestants...\n"RC);
	while (tmp)
	{
		tmp->num = number++;
		if (is_visual == 0)
			ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\")\n",
					  tmp->num, tmp->head.prog_size, tmp->head.prog_name,
					  tmp->head.comment);
		tmp = tmp->next;
	}
}

int		check_flags_corewar(t_bs *bs, char **av, int ac, int *index)
{
	if (ft_strequ(av[*index], "-dump") || ft_strequ(av[*index], "-print") ||
		ft_strequ(av[*index], "-n") || ft_strequ(av[*index], "-v") ||
		ft_strequ(av[*index], "-a") || ft_strequ(av[*index], "-b"))
	{
		parse_flag_dump(bs, av, ac, index);
		parse_flag_print(bs, av, ac, index);
		parse_flag_visual_aff_beep(bs, av, index);
	}
	return (0);
}

void	check_is_flags(t_bs *bs)
{
	if (bs->is_visual)
	{
		bs->is_dump = 0;
		bs->is_print = 0;
		bs->is_aff = 0;
	}
}

//TODO перевірка на сумісність декількох флагів
void	ft_sprint(t_bs *base, char **av, int ac)
{
	int				i;
	unsigned int	num_player;
	int fd;

	i = 1;
	while (i < ac)
	{
		num_player = 0;
		if (check_flags_corewar(base, av, ac, &i))
			num_player = parse_flag_num(base, av, ac, &i);
		if ((fd = open(av[i], O_RDONLY)) != -1)
		{
			close(fd);
			check_is_flags(base);
			add_new_champ(&base->list_champs, num_player, &base->list_proc);
			ft_magic_size(av[i], &base->list_champs->head);
			ft_name_comment(av[i], &base->list_champs->head, 0);
			ft_name_comment(av[i], &base->list_champs->head, 1);
			ft_instraction(av[i], base);
		}
		i++;
	}
	if (base->list_champs == NULL)
		ft_error(13, NULL);
	base->winner = base->list_champs->num;
}

void	print_winner(t_chmp *list_champs, unsigned int winner)
{
	t_chmp *tmp;

	tmp = list_champs;
	while (tmp)
	{
		if (winner == tmp->num)
		{
			ft_printf("Contestant %u, \"%s\", has won !\n", winner,
					  tmp->head.prog_name);
			return ;
		}
		tmp = tmp->next;
	}
}

unsigned int g_count;

int 	main(int argc, char **argv)
{
	t_bs		base;

	if (argc == 1)
		ft_error(1, NULL);
	if (check_op_h() == 0)
		return (1);
	base_to_zero(&base);
	ft_sprint(&base, argv, argc);
	num_champs(base.list_champs, base.is_visual);
	ft_fill_map(&base);
	if (base.is_visual == 0)
		print_winner(base.list_champs, base.winner);
	del_list_champ(&base.list_champs);
	del_list_proc(&base.list_proc);
	return (0);
}
