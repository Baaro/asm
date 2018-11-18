/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:55:19 by vsokolog          #+#    #+#             */
/*   Updated: 2018/02/26 22:55:21 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <wchar.h>
# include "libft.h"

# define FLAGS "-+ #0"
# define TYPES "sScCdD%ioOuUxXpn"
# define ABS(x)  x = own_abs(x);
# define ARG (**arg)
# define FLAGS_TO_ZERO(i) while ((i) != 6) arg.flags[(i)++] = 0;
# define MINUS 0
# define PLUS 1
# define SPACE 2
# define HESH 3
# define ZERO 4
# define NEGATIVE 5

# define RESET      "\x1b[0m"

# define INVERT     "\x1b[7m"
# define BOLD       "\x1b[1m"
# define UNDERLINE  "\x1b[4m"

# define RED        "\x1b[31m"
# define CYAN       "\x1b[36m"
# define WHITE      "\x1b[37m"
# define BLACK      "\x1b[30m"
# define GREEN      "\x1b[32m"
# define YELLOW     "\x1b[33m"
# define BLUE       "\x1b[34m"
# define MAGENTA    "\x1b[35m"
# define F_RESET    "\x1b[39m"

# define BACKGROUND_BLACK    "\x1b[40m"
# define BACKGROUND_RED      "\x1b[41m"
# define BACKGROUND_YELLOW   "\x1b[43m"
# define BACKGROUND_BLUE     "\x1b[44m"
# define BACKGROUND_GREEN    "\x1b[42m"
# define BACKGROUND_MAGENTA  "\x1b[45m"
# define BACKGROUND_CYAN     "\x1b[46m"
# define BACKGROUND_WHITE    "\x1b[47m"
# define BACKGROUND_RESET    "\x1b[49m"

typedef struct	s_form
{
	char		*n;
	char		*flg;
	char		*p;
	char		*w;
}				t_form;

typedef enum	e_length
{
	hh = 1,
	h,
	l,
	ll,
	t,
	j,
	z,
	L
}				t_l;

typedef struct	s_arg
{
	bool		flags[6];
	char		type;
	t_l			l_size;
	int			precision;
	int			width;
	int			len;
	t_form		fm;
}				t_arg;

int				ft_printf(const char *format, ...);

void			parsing(char **f, va_list ap, t_arg *arg);
void			pars_length(char **f, t_arg **arg);
void			pars_precision(char **f, va_list ap, t_arg **arg);

void			form(va_list ap, t_arg *arg);
void			form_nums(t_arg **arg, va_list ap);
void			form_str(t_arg **arg, va_list ap);
void			form_char(t_arg **arg, va_list ap);
void			form_wchar(t_arg **arg, va_list ap);
void			form_wstr(t_arg **arg, va_list ap);
void			form_n(t_arg *arg, va_list ap);

void			get_integer(char **num, va_list ap, t_arg *arg);
void			get_hexa(char **num, va_list ap, t_arg *arg);
void			get_octal(char **num, va_list ap, t_arg *arg);
void			get_unsigned(char **num, va_list ap, t_arg *arg);

void			get_width_precision_num(char **p, char **w, t_arg arg, int n);
void			get_width_str_char(t_arg *arg, int l_src);
void			get_width_wstr(t_arg *arg, int size);
/*
** auxiliary functions
*/
char			*ft_uns_itoabase(uintmax_t value, uintmax_t base);
char			*ft_itoabase(intmax_t value, int base, t_arg *arg);
char			*output_by_order(char *s1, char *s2, char *s3, char *s4);
bool			is_zero(char *s_num);
void			empty(char **str);
void			ft_hesh(char **flg, t_arg arg);
void			output(t_arg *arg, char *str);
void			correct_flags(t_arg **arg);
int				count_bits(int value);
int				wstrlen(wchar_t *wstr);
intmax_t		own_abs(intmax_t val);

#endif
