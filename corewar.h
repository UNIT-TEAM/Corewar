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
**	dump	- number of cycles;
**	proc	- struct of prog_counter;
**	chmp	- struct of champion;
**		num	- number of player;
*/

# define COMMENT_POS	(PROG_NAME_LENGTH + 13 - ((PROG_NAME_LENGTH + 1) % 4))
# define SIZE_POS		(PROG_NAME_LENGTH + 9 - ((PROG_NAME_LENGTH + 1) % 4))
# define CODE_POS		(PROG_NAME_LENGTH + 10 + COMMENT_LENGTH + ((4 - \
						((PROG_NAME_LENGTH + 1) % 4)) * 2))

unsigned int 		g_count;

typedef struct 		s_proc
{
	unsigned int	pc;
	unsigned int	regs[REG_NUMBER];
	char 			carry;
	struct s_chmp	*next;
}					t_proc;

typedef struct		s_chmp
{
	header_t		head;
	int 			live;
	unsigned int 	num;
	t_proc			*proc_1;
	unsigned char	*instructions;
	struct s_chmp	*next;
}					t_chmp;

typedef	struct		s_bs
{
	t_chmp			*list_champs;
	unsigned char 	map[MEM_SIZE];
	int 			np;
	int				pftr;
	unsigned int 	dump;
	char 			is_dump;
}					t_bs;

void 	ft_error(int i, char *str);

void 	fill_magic(unsigned int *magic_size, unsigned char *buf, char *str,\
				int flag);
void 	ft_magic_size(char *av, header_t *p);

void 	ft_name_comment(char *av, header_t *p, int flag);
void	ft_instraction(char *av, t_bs *bs);

void	add_new_champ(t_chmp **first, unsigned int num_player);

void ft_fill_map(t_bs *bs);



#endif
