/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:09:37 by ysalata           #+#    #+#             */
/*   Updated: 2017/10/24 18:47:43 by ysavenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include "op.h"

# define UI unsigned int
# define SPACE(c) ((c) == '\t' || (c) == ' ' || (c) == '\v') ? 1 : 0
# define NAME NAME_CMD_STRING
# define C COMMENT_CMD_STRING
# define LABEL LABEL_CHAR
# define IS_DIR(a) ((a) == DIRECT_CHAR ) ? 1 : 0
# define IS_LBL(b) ((b) == LABEL_CHAR ? 1 : 0)
# define IS_COM(u) (((u) == COMMENT_CHAR || (u) == ';') ? 1 : 0)
# define SWAP_USI(i) (((i) << 8) | ((i) >> 8 & 0xFF))
# define SWAP_UI(i) (((i) << 16) | ((i) >> 16))

static char *g_er[] = {
	": Can't open() file.\n",
	": Can't read() file.\n",
	": Empty file\n",
	": Repeating .name field.\n",
	": Repeating .comment field.\n",
	": .name field is absent or was incorrect written.\n",
	": .comment field is absent or was incorrect written.\n",
	": Empty line in header.\n",
	": Opening brackets wasn't found.\n",
	": get_next_line() failed.\n",
	": The presence of third-party characters after the line.\n",
	": .name length exceeds the allowable rate.\n",
	": .comment length exceeds the allowable rate.\n",
	": Label name is empty.\n",
	": Label name consisting non-LABEL_CHAR characters.\n",
	": Invalid command name.\n",
	": Invalid number of command arguments.\n",
	": Empty argument.\n",
	": Register argument value higher, than REGISTER_NUMBER.\n",
	": Invalid argument type.\n",
	": Calling of non-existing label.\n",
	": \\n or comment line in the end of file required.\n",
	": Undefined symbols after .name string.\n",
	": Undefined symbols after .comment string.\n",
	": Bot instructions didn't found.\n",
	": Can't create a .cor file\n",
	": Undefined symbols after instruction string.\n",
	": Declaring string with .comment before .name string\n"
};

typedef struct		s_cmnd
{
	int				r;
	int				cmd;
	int				start;
	int				line;
	int				size;
	char			cipher;
	int				num;
	char			*name;
	char			**args;
	unsigned int	i_arg[MAX_ARGS_NUMBER];
	struct s_cmnd	*next;
	struct s_cmnd	*prev;
}					t_cmnd;

typedef struct		s_label
{
	int				line;
	int				start;
	char			*name;
	struct s_label	*next;
	struct s_label	*prev;
}					t_label;

typedef struct		s_asm
{
	int				lines;
	char			*name;
	char			*comm;
	t_cmnd			*cmnd;
	t_label			*labl;
}					t_asm;

typedef struct		s_op
{
	char			*op;
	int				arg;
	char			kind[MAX_ARGS_NUMBER];
	int				num;
	int				cycle;
	char			*msg;
	int				id1;
	int				id2;
}					t_op;

static t_op			g_tab[17] = {
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, \
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, \
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, \
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, \
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, \
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

unsigned int g_bytes;
int g_fd;
int g_i;
char *g_s;
t_asm *g_file;
t_header *g_head;

int					cw_e(int type);
char				*cw_cut(char *s);
unsigned int		cw_endian(unsigned int i);
int					cw_check_value(t_cmnd *cmnd, int j, char *label, int i);
int					cw_write_cmd(t_cmnd *cmnd, int type, int i);
int					cw_args_parse(int i, char *arg, t_cmnd *cmnd);
t_cmnd				*cw_cmnd_init(int *i);
int					cw_cmd(int i, int j, int cmd, int k);
int					cw_label(int start, int len);
int					cw_head_clean(int type, int i, int j);
int					cw_head_parse(int i, char *dst, char *str, int type);
int					cw_read_head(int error);
int					cw_calllabel(char *s, t_cmnd *c, int i, int type);
int					cw_check_label(int error);
int					cw_check_end(int i);
void				cw_write_code(t_cmnd *tmp, int fd);
int					cw_write_all(char *name, t_cmnd *tmp);
int					cw_file_analyze(int lines, char *file, int len, int error);

#endif
