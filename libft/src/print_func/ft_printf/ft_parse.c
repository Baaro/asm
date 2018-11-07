/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 22:04:49 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/02/25 19:20:35 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_flags(t_pr *pr)
{
	while ((pr->n = ft_strnchr("-+ #0*", *pr->format)) > -1
			&& pr->format++)
		pr->fl |= (1 << pr->n);
	if ((pr->fl & FL_MINUS) && !(pr->fl & FL_WILD))
		pr->fl &= ~FL_ZERO;
	if (pr->fl & FL_PLUS)
		pr->fl &= ~FL_SPACE;
}

static void		ft_parse_width_precision(t_pr *pr)
{
	if (ft_isdigit(*pr->format) && *pr->format != '0')
	{
		pr->width = ft_max(1, ft_atoi(pr->format));
		while (ft_isdigit(*pr->format))
			pr->format++;
	}
	if (*pr->format == '.')
	{
		pr->format++;
		pr->precision = ft_max(0, ft_atoi(pr->format));
		while (ft_isdigit(*pr->format))
			pr->format++;
		pr->fl |= FL_PREC;
	}
}

static void		ft_parse_length(t_pr *pr)
{
	if (*pr->format == 'h')
		pr->fl |= ((pr->format[1] == 'h' && pr->format++) ? FL_SHS : FL_SH);
	else if (*pr->format == 'l')
		pr->fl |= ((pr->format[1] == 'l' && pr->format++) ? FL_LONGL : FL_LONG);
	else if (*pr->format == 'j')
		pr->fl |= FL_INTMAX;
	else if (*pr->format == 'z')
		pr->fl |= FL_SITE_T;
	else
		return ;
	pr->format++;
}

static void		ft_parse_type(t_pr *pr)
{
	pr->c = *pr->format;
	if (ft_strchr("SDOUXC", pr->c))
	{
		pr->fl |= (pr->c != 'X') ? FL_LONG : FL_UPERCASE;
		pr->c += 32;
	}
	if (pr->c == 'c')
		pf_char(pr, va_arg(pr->list, unsigned));
	else if (pr->c == 's')
		pf_string(pr);
	else if (ft_strchr("di", pr->c))
		pf_number(pr, 10);
	else if (ft_strchr("oux", pr->c))
		pf_number_un(pr, ft_strnchr("....ou..x", pr->c) << 1);
	else if (pr->c == 'p')
		pf_pointer(pr);
	else
		ft_without_type(pr);
}

void			ft_parse(t_pr *pr)
{
	ft_parse_flags(pr);
	ft_parse_width_precision(pr);
	ft_parse_length(pr);
	ft_parse_type(pr);
	ft_erase_flags(pr);
}
