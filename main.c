#include "corewar.h"



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

int		check_flags_corewar(char **av, int *index)
{
	return (ft_strequ(av[*index], "-dump") || ft_strequ(av[*index], "-print") ||
			ft_strequ(av[*index], "-n") || ft_strequ(av[*index], "-v") ||
			ft_strequ(av[*index], "-a") || ft_strequ(av[*index], "-b"));
}

void	check_is_flags(t_bs *bs)
{
	if (bs->is_visual)
	{
		bs->is_dump = 0;
		bs->is_print = 0;
		bs->is_aff = 0;
	}
	else if (bs->is_dump && bs->is_print)
		bs->is_print = 0;
}

void	ft_sprint(t_bs *base, char **av, int ac)
{
	int				i;
	unsigned int	num_player;
	int fd;

	i = 1;
	while (i < ac)
	{
		num_player = 0;
		if (check_flags_corewar(av, &i))
		{
			num_player = parse_flag_num(base, av, ac, &i);
			parse_flag_dump(base, av, ac, &i);
			parse_flag_print(base, av, ac, &i);
			parse_flag_visual_aff_beep(base, av, &i);
		}
		if (!check_flags_corewar(av, &i) && i < ac)
		{
			check_is_flags(base);
			add_new_champ(&base->list_champs, num_player, &base->list_proc,
						  av[i]);
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
