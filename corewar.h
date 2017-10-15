#ifndef COREWAR_H
#define COREWAR_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

/*
**	p		- players in project;
** 	np		- number of players;
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
    unsigned char 	is_codage;
    unsigned char	dir_size;
}					t_op;

typedef struct 		s_proc
{
	unsigned int	pc;
	unsigned int	regs[REG_NUMBER];
	unsigned short	carry;
	unsigned short	is_live;
    unsigned int    inst_cycle;
	unsigned int	id;

	struct s_proc	*next;
}					t_proc;

typedef struct		s_chmp
{
	header_t		head;
	int 			live;
	unsigned int	cycle_live;
	unsigned int 	num;
	unsigned char	*instructions;
	unsigned int	flag_num;
	struct s_chmp	*next;
}					t_chmp;

typedef	struct		s_bs
{
	t_chmp			*list_champs;
	t_proc			*list_proc;
	unsigned char 	map[MEM_SIZE];
	int 			np;
	unsigned int	winner;
	unsigned short	is_num_flag;
	unsigned int 	dump;
	char 			is_dump;
	unsigned int	cycle_print;
	char 			is_print;
}					t_bs;

extern  t_op		op_tab[17];
extern unsigned int g_count;

void 	ft_error(int i, char *str);

void 	fill_magic(unsigned int *magic_size, unsigned char *buf, char *str,\
				int flag);
void 	ft_magic_size(char *av, header_t *p);

void 	ft_name_comment(char *av, header_t *p, int flag);
void	ft_instraction(char *av, t_bs *bs);

void	add_new_champ(t_chmp **first, unsigned int num_player, t_proc **proc);

void ft_fill_map(t_bs *bs);
void	print_map(unsigned char *map);

int		check_op_h();

unsigned int	*take_argument(unsigned char *map, unsigned char codage,
						  t_proc *proc, unsigned short op_index);
int		check_codage(unsigned char codage, t_proc *proc, unsigned short index);

void	shift_pc(unsigned char codage, t_proc *proc, unsigned short op_index);


void	ft_live(unsigned char *map, t_proc *proc, unsigned short op_index,
				t_chmp *champs);
void	ft_ld_lld_ldi_lldi(unsigned char *map, t_proc *proc,
						   unsigned short op_index);
void	ft_st_sti(unsigned char *map, t_proc *proc, unsigned short op_index);
void	ft_add_sub_and_or_xor(unsigned char *map, t_proc *proc,
							  unsigned short op_index);
void	ft_zjump(unsigned char *map, t_proc *proc, unsigned short index);
void	ft_fork_lfork(unsigned char *map, t_proc **procs, t_proc *tmp,
					  unsigned short op_index);
void	ft_aff(unsigned char *map, t_proc *proc, unsigned short op_index);

#endif
