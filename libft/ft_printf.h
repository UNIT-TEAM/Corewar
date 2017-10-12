/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgogol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:38:58 by tgogol            #+#    #+#             */
/*   Updated: 2017/04/11 14:39:01 by tgogol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

/*
** Reset color
*/
# define RC "\x1B[0m"

/*
** Main color
*/

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"

/*
** High Intensity Backgrounds color
*/

# define BGIRED "\x1B[101m"
# define BGIGRN "\x1B[102m"
# define BGIYEL "\x1B[103m"
# define BGIBLU "\x1B[104m"
# define BGIMAG "\x1B[105m"
# define BGICYN "\x1B[106m"
# define BGIWHT "\x1B[107m"

/*
** Backgrounds color
*/

# define BGRED "\x1B[41m"
# define BGGRN "\x1B[42m"
# define BGYEL "\x1B[43m"
# define BGBLU "\x1B[44m"
# define BGMAG "\x1B[45m"
# define BGCYN "\x1B[46m"
# define BGWHT "\x1B[47m"

/*
** Bold
*/

# define BRED "\x1B[1;31m"
# define BGRN "\x1B[1;32m"
# define BYEL "\x1B[1;33m"
# define BBLU "\x1B[1;34m"
# define BMAG "\x1B[1;35m"
# define BCYN "\x1B[1;36m"
# define BWHT "\x1B[1;37m"

/*
** Single underline
*/

# define URED "\x1B[4;31m"
# define UGRN "\x1B[4;32m"
# define UYEL "\x1B[4;33m"
# define UBLU "\x1B[4;34m"
# define UMAG "\x1B[4;35m"
# define UCYN "\x1B[4;36m"
# define UWHT "\x1B[4;37m"

/*
** Bold single underline
*/

# define BURED "\x1B[1;4;31m"
# define BUGRN "\x1B[1;4;32m"
# define BUYEL "\x1B[1;4;33m"
# define BUBLU "\x1B[1;4;34m"
# define BUMAG "\x1B[1;4;35m"
# define BUCYN "\x1B[1;4;36m"
# define BUWHT "\x1B[1;4;37m"

/*
** Bold single underline High Intensity
*/

# define BUIRED "\x1B[1;4;91m"
# define BUIGRN "\x1B[1;4;92m"
# define BUIYEL "\x1B[1;4;93m"
# define BUIBLU "\x1B[1;4;94m"
# define BUIMAG "\x1B[1;4;95m"
# define BUICYN "\x1B[1;4;96m"
# define BUIWHT "\x1B[1;4;97m"

/*
** High bold Intensity
*/

# define BIRED "\x1B[1;91m"
# define BIGRN "\x1B[1;92m"
# define BIYEL "\x1B[1;93m"
# define BIBLU "\x1B[1;94m"
# define BIMAG "\x1B[1;95m"
# define BICYN "\x1B[1;96m"
# define BIWHT "\x1B[1;97m"

/*
** High Intensity
*/

# define IRED "\x1B[91m"
# define IGRN "\x1B[92m"
# define IYEL "\x1B[93m"
# define IBLU "\x1B[94m"
# define IMAG "\x1B[95m"
# define ICYN "\x1B[96m"
# define IWHT "\x1B[97m"

/*
** str		save string
** nw		save number of width
** bfita	base for itoa_base
** r		return value
** *nbr		for va_arg;
** mdf		j, z, ll, l, h, hh
** prc		precision
** tp		sSpdDioOuUxXcC
*/

typedef struct		s_prntf
{
	char			*str;
	int				nw;
	int				m;
	int				z;
	int				hash;
	int				pls;
	int				spc;
	int				bfita;
	int				r;
	void			*nbr;
	char			mdf;
	int				prc;
	char			tp;

}					t_prntf;

int					ft_printf(char *format, ...);
void				ft_strclear(char **s, char **str);
void				skip_flags_length_type(char **s, t_prntf *bs);

void				fill_digit(char *s, t_prntf *base, va_list ap);
void				fill_flags(char *s, t_prntf *bs);
void				fill_basetoziro(t_prntf *bs);

void				fill_modificator(char *s, char *mdf);
void				fill_priority(t_prntf **bs);
void				fill_bitoa(char c, int *bitoa);
void				fill_type(char *s, char *tp);
int					check_afte_pers(char c);

int					check_type(char c);
int					check_flags(char c);
int					check_length(char c);
int					check_minus_in_type(char c);
int					isdigit_withoutziro(char c);

char				*ft_itoab_u(long unsigned int value, int base, char c);
char				*ft_itoa_b(intmax_t value, int base);

void				print_aka_flags(int wl, char c, t_prntf *bs);
void				print_prc(t_prntf *bs);
void				print_prc_m(t_prntf *bs);

void				cast_di(t_prntf *bs);
void				cast_uox(t_prntf *bs);
void				print_di_m(t_prntf *bs);
void				print_p(t_prntf *bs);
void				print_di(t_prntf *bs);

void				print_u(t_prntf *bs);
void				print_o(t_prntf *bs);
void				print_x(t_prntf *bs);
void				print_b(t_prntf *bs);
void				do_n(t_prntf *bs);

void				print_width(t_prntf *bs, int fhesh, int fchar);
void				print_s(t_prntf *bs);
void				print_c(t_prntf *bs);
void				print(t_prntf *bs);
void				print_symbol(char **format, t_prntf *bs);

void				check_bit(int *nbr, int *r);
void				print_upper_s(int *s, int *r, int size, int f);

#endif
