/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 22:05:34 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/25 18:58:04 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>

# define ABS(a)			(a > 0) ? a : -a
# define MAX(a, b)		(a > b) ? a : b
# define MIN(a, b)		(a > b) ? b : a

# define FL_MINUS		(1 << 0)
# define FL_PLUS		(1 << 1)
# define FL_SPACE		(1 << 2)
# define FL_HASH		(1 << 3)
# define FL_ZERO		(1 << 4)
# define FL_WILD		(1 << 5)
# define FL_UPERCASE	(1 << 6)
# define FL_PREC		(1 << 7)
# define FL_SH			(1 << 8)
# define FL_SHS			(1 << 9)
# define FL_LONG		(1 << 10)
# define FL_LONGL		(1 << 11)
# define FL_INTMAX		(1 << 12)
# define FL_SITE_T		(1 << 13)
# define FL_POINTER		(1 << 14)

typedef struct		s_pr
{
	int					fl;
	int					n;
	char				c;
	va_list				list;
	size_t				size;
	int					width;
	int					precision;
	int					padding;
	char				*buff;
	unsigned			buff_len;
	char				*format;
}					t_pr;

int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);
void				ft_parse(t_pr *pr);
void				ft_erase_flags(t_pr *pr);
void				ft_without_type(t_pr *pr);

void				ft_padding(t_pr *pr, int n);
void				ft_buffer(t_pr *pr, char *str, size_t size);
void				ft_buffer_char(t_pr *pr, char c);
void				ft_realloc(t_pr *pr);

void				pf_char(t_pr *pr, unsigned s);
void				pf_string(t_pr *pr);

void				pf_number(t_pr *pr, short base);
void				pf_number_un(t_pr *pr, short base);
int					pf_itoa_base(t_pr *pr, uintmax_t n, short b, char **str);
void				pf_itoa_un(t_pr *pr, uintmax_t n, short base);
void				pf_pointer(t_pr *pr);

#endif
