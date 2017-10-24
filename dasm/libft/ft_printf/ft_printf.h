/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 17:31:36 by ysalata           #+#    #+#             */
/*   Updated: 2017/05/22 18:51:13 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

# define TRUE	1
# define FALSE	0

# define COL_BLACK			"\x1B[22;30m"
# define COL_RED				"\x1B[22;31m"
# define COL_GREEN			"\x1B[22;32m"
# define COL_BROWN			"\x1B[22;33m"
# define COL_BLUE				"\x1B[22;34m"
# define COL_MAGENTA		"\x1B[22;35m"
# define COL_CYAN			"\x1B[22;36m"
# define COL_GRAY				"\x1B[22;37m"
# define COL_DGRAY			"\x1B[01;30m"
# define COL_LRED				"\x1B[01;31m"
# define COL_LGREEN			"\x1B[01;32m"
# define COL_LYELLOW		"\e[38;5;220m"
# define COL_LBLUE			"\x1B[01;34m"
# define COL_LMAGENTA		"\x1B[01;35m"
# define COL_LCYAN			"\x1B[01;36m"
# define COL_WHITE			"\x1B[01;37m"
# define COL_EOC				"\x1B[0m"

union				u_type
{
	char			c;
	char			*s;
	wchar_t			*ls;
};

typedef struct		s_format
{
	int				len;
	int				i_pos;
	int				retval;
}					t_format;

typedef struct		s_specif
{
	int				space;
	int				m;
	int				plus;
	int				znak;
	int				hash;
	int				modif;
	int				zero;
	int				width;
	int				ac;
	int				len;
	int				coef;
	long long int	num;
	char			lol;
	char			type;
	char			*lick;
	union u_type	slen;
}					t_spesif;

typedef void	(*t_proto)(va_list *, t_format *, t_spesif *);

typedef struct		s_func
{
	t_proto			fun[123];
}					t_func;
int					ft_printf(char *format, ...);
size_t				ft_wstrlen(wchar_t *s);
int					ft_tolower(int c);
char				*ft_unitoabase(unsigned long long int n, int base,
					char *lick);
char				*ft_itoabase(long long int n, int base, char *l);
void				ft_write(char *a, int i);
int					ft_swrite(char *a, t_format *tf, int howmuch);
void				ft_lswrite(int *value, t_format *tf,
					int howmuch, int coef);
char				*ft_kstrchr(const char *s, int c);
void				prf_putstr(char const *s, int *i);
int					str_error(t_spesif *spec, int *retval);
void				s_n(va_list *ap, t_format *tform, t_spesif *spec);
void				s_decimal(va_list *ap, t_format *tform,
					t_spesif *s);
void				s_unsig(va_list *ap, t_format *tform,
					t_spesif *s);
void				s_string(va_list *ap, t_format *tform,
					t_spesif *s);
void				s_char(va_list *ap, t_format *tform,
					t_spesif *spec);
unsigned long long	tsize_uns(int i, va_list ap);
long long int		tsize_dec(int i, va_list ap);
long long int		*tsize_n(int i, va_list ap);
int					choose_sys(char b);
void				create_srtuct(t_spesif *spec);
int					ft_checkstr(char *str, t_spesif *spec, int base);
void				little_check(t_spesif *spec, char *format,
					int *i);
int					parse_line(t_func *flags, t_format *tform,
					char *f, va_list *ap);
#endif
