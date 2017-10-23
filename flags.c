#include "corewar.h"

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
