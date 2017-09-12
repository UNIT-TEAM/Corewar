#include "corewar.h"

/*
** flag == 1 for magic;
** flag == 0 for prog_size;
*/

int		check_size(char *av)
{
	char	*tmp;
	int 	fd;
	int 	i;

	i = 0;
	tmp = 0;
	fd = open(av, O_RDONLY);
	(lseek(fd, CODE_POS, SEEK_SET) < 0) ? ft_error(2, NULL) : 0;
	while (read(fd, &tmp, 1))
		i++;
	close(fd);
	return (i);
}

void 	fill_magic(unsigned int *magic_size, unsigned char *buf, char *str,
				   int flag)
{
	int				i;
	unsigned char	tmp[4];

	/*shift = 0xffffffff;
	k = 24;
	i = -1;
	while (++i < 4)
	{
		arr[i] = (i == 0) ? (unsigned int)(buf[i] << k) : (buf[i] << k & shift);
		k -= 8;
		shift = shift >> 8;
	}*/
	i = -1;
	while (++i < 4)
		tmp[3 - i] = buf[i];

	*magic_size = *((unsigned int *)tmp);
	(*magic_size != COREWAR_EXEC_MAGIC && flag) ?	ft_error(3, str) : 0;
	if (*magic_size  > CHAMP_MAX_SIZE && !flag)
	{
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has too large a code (%u"\
		" bytes vs %u bytes)\n", str, *magic_size, CHAMP_MAX_SIZE);
		exit(1);
	}
	if (*magic_size != (unsigned int)check_size(str) && !flag)
		ft_error(4, str);
}

void 	ft_magic_size(char *av, header_t *p)
{
	int				fd;
	unsigned char 	buf[4];

	fd = open(av, O_RDONLY);
	if (read(fd, &buf, 4) == -1)
	{
		close(fd);
		ft_error(2, NULL);
	}
	fill_magic(&p->magic, buf, av, 1);
	close(fd);
	fd = open(av, O_RDONLY);
	(lseek(fd, SIZE_POS, SEEK_SET) < 0) ? ft_error(2, NULL) : 0;
	if (read(fd, &buf, 4) == -1)
	{
		ft_error(2, NULL);
		close(fd);
	}
	fill_magic(&p->prog_size, buf, av, 0);
	close(fd);
}

/*
** flag 0 for name;
** flaf 1 for comment;
**
*/

void 	ft_name_comment(char *av, header_t *p, int flag)
{
	int 	fd;
	int 	k;

	fd = open(av, O_RDONLY);
	k = (flag == 0) ? 4 : COMMENT_POS;
	(lseek(fd, k, SEEK_SET) < 0) ? ft_error(2, NULL) : 0;
	if (flag == 0)
		(read(fd, &p->prog_name, PROG_NAME_LENGTH + 1) == -1) ?\
		ft_error(2, NULL) : 0;
	else
		(read(fd, &p->comment, COMMENT_LENGTH + 1) == -1) ?\
		ft_error(2, NULL) : 0;
	close(fd);
}

void	ft_instraction(char *av, t_bs *bs)
{
	int		fd;
	int		k;

	k = 0;
	fd = open(av, O_RDONLY);
	(lseek(fd, CODE_POS, SEEK_SET) < 0) ? ft_error(2, NULL) : 0;
	//bs->pftr = (i == 0) ? 0 : bs->pftr + MEM_SIZE / bs->np;
	//визначення початкової позиції гравця на карті для запису його інструкцій на карту
	if (!(bs->list_champs->instructions = (unsigned char *)malloc(sizeof\
	(unsigned char) * bs->list_champs->head.prog_size)))
	{
		close(fd);
		ft_error(5, av);
	}
	while (read(fd, &bs->list_champs->instructions[k], 1))
		k++;
	close(fd);
	(k == 0) ? ft_error(4, av) : 0;
	if (!(bs->list_champs->proc_1 = (t_proc *)malloc(sizeof(t_proc))))
		ft_error(5, av);
	bs->np++;
	bs->list_champs->proc_1->regs[0] = (unsigned int)(bs->np * -1);

}