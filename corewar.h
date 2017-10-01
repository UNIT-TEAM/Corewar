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
// !!!!!!!!!!!!!!!!!!!!!!

typedef struct		s_op
{
    char			*name;
    unsigned short	count_arg;
    t_arg_type		arg[3];
    unsigned short	opcode;
    unsigned short	cycles;
    unsigned char 	codage;
    unsigned char	dir;
}					t_op;

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
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

unsigned int 		g_count;




typedef struct 		s_proc
{
	unsigned int	pc;
	unsigned int	regs[REG_NUMBER];
	char 			carry;
    unsigned int    cycle_to_die;
    unsigned int    inst_cycle;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_chmp
{
	header_t		head;
	int 			live;
	unsigned int 	num;
	unsigned char	*instructions;
	struct s_chmp	*next;
}					t_chmp;

typedef	struct		s_bs
{
	t_chmp			*list_champs;
	t_proc			*list_proc;
	unsigned char 	map[MEM_SIZE];
	int 			np;
	int				pftr;
	unsigned int 	dump;
	char 			is_dump;
	unsigned int	dump_go;
	char 			is_dump_go;
}					t_bs;

void 	ft_error(int i, char *str);

void 	fill_magic(unsigned int *magic_size, unsigned char *buf, char *str,\
				int flag);
void 	ft_magic_size(char *av, header_t *p);

void 	ft_name_comment(char *av, header_t *p, int flag);
void	ft_instraction(char *av, t_bs *bs);

void	add_new_champ(t_chmp **first, unsigned int num_player, t_proc **proc);

void ft_fill_map(t_bs *bs);

void	sti(unsigned char *map, t_proc *proc);




#endif
