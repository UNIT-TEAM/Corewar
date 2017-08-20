#include "corewar.h"

/*
** flag == 1 for magic;
** flag == 0 for prog_size;
*/

void 	fill_magic(unsigned int *magic_size, char *buf, char *str, int flag)
{
	int				k;
	int 			i;
	unsigned int 	shift;
	unsigned int	arr[4];

	shift = 0xffffffff;
	k = 24;
	i = -1;
	while (++i < 4)
	{
		arr[i] = (i == 0) ? (unsigned int)(buf[i] << k) : (buf[i] << k & shift);
		k -= 8;
		shift = shift >> 8;
	}
	((*magic_size = arr[0] | arr[1] | arr[2] | arr[3]) != COREWAR_EXEC_MAGIC &&
		flag) ?	ft_error(3, str) : 0;
	if ((*magic_size = arr[0] | arr[1] | arr[2] | arr[3]) > CHAMP_MAX_SIZE &&
	 !flag)
	{
		ft_printf(RED"Error:"RC" File "BLU"%s"RC" has too large a code (%u"\
		" bytes vs %u bytes)\n", str, *magic_size, CHAMP_MAX_SIZE);
		exit(1);
	}

}

void 	ft_magic_size(char *av, header_t *p)
{
	int				fd;
	char 			buf[4];

	fd = open(av, O_RDONLY);
	if (read(fd, &buf, 4) == -1)
	{
		ft_error(2, NULL);
		close(fd);
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

void	ft_instraction(char *av, t_bs *bs, int i)
{
	int		fd;
	int		r;
	char 	*tmp;

	tmp = 0;
	fd = open(av, O_RDONLY);
	(lseek(fd, CODE_POS, SEEK_SET) < 0) ? ft_error(2, NULL) : 0;
	bs->pftr = (i == 0) ? 0 : bs->pftr + MEM_SIZE / bs->np;
	r = get_next_line(fd, &tmp);
	(r <= 0 && !(tmp)) ? ft_error(4, av) : 0;
	ft_strcpy(bs->map + bs->pftr, tmp);
}