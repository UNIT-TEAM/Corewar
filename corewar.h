#ifndef COREWAR_H
#define COREWAR_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

/*
**	p		- players in project;
** 	np		- number of players;
** 	pftr	- position flags to write players instructions to map;
**	tmpn	- temp number of player;
**	tmpd	- temp number of cycles;
**	prco	- struct of prog_counter;
**	chmp	- struct of champion;
**		n	- number of player;
**	plr		- list of players;
*/

# define COMMENT_POS	(PROG_NAME_LENGTH + 13 - ((PROG_NAME_LENGTH + 1) % 4))
# define SIZE_POS		(PROG_NAME_LENGTH + 9 - ((PROG_NAME_LENGTH + 1) % 4))
# define CODE_POS		(PROG_NAME_LENGTH + 10 + COMMENT_LENGTH + ((4 - \
						((PROG_NAME_LENGTH + 1) % 4)) * 2))
typedef struct 		s_prco
{
	int 			pc;
	unsigned int	r[REG_NUMBER]; //REG_SIZE як сюди його прикрутити
	struct s_chmp	*nx;
}					t_prco;

typedef struct		s_chmp
{
	int 			live;
	char 			carry;
	short			n;
	struct s_chmp	*nx;
}					t_chmp;
typedef	struct		s_bs
{
	header_t		p[MAX_PLAYERS];
	char 			*instruct;
	char 			map[MEM_SIZE];
	int 			np;
	int				pftr;
	unsigned int	*pc;
	unsigned int	r[REG_NUMBER];
	int 			dump;
	int 			tmpn;
	int				tmpd;
	t_chmp			*plr;
}					t_bs;

void 			ft_error(int i, char *str);

void 			fill_magic(unsigned int *magic_size, char *buf, char *str,\
				int flag);
void 			ft_magic_size(char *av, header_t *p);

void 			ft_name_comment(char *av, header_t *p, int flag);
void			ft_instraction(char *av, t_bs *bs, int i);

#endif
