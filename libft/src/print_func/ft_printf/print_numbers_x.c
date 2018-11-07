/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:38:57 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/04/27 20:39:01 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_itoa_print_pref(t_pr *pr, uintmax_t n, short base)
{
	if ((n || (pr->fl & FL_POINTER)) && (pr->fl & FL_HASH) && ((base == 16)))
		ft_buffer_char(pr, 48);
	if ((pr->fl & FL_HASH) && (base == 8 &&
			(n || (!n && !pr->precision && (pr->fl & FL_PREC)))))
		ft_buffer_char(pr, 48);
	if ((n || (pr->fl & FL_POINTER)) && (pr->fl & FL_HASH) && base == 16)
		ft_buffer_char(pr, (pr->fl & FL_UPERCASE) ? 'X' : 'x');
}

void	pf_itoa_un(t_pr *pr, uintmax_t n, short base)
{
	uintmax_t		m;
	int				len;
	char			*str;

	m = n;
	len = 0;
	while (m && ++len)
		m /= base;
	((pr->fl & FL_HASH) && base == 8 && n) ? pr->width-- : 0;
	((pr->fl & FL_HASH) && base == 16 && (n || (pr->fl & FL_POINTER)))
			? pr->width -= 2 : 0;
	if (pr->fl & FL_ZERO && !(pr->fl & FL_PREC))
	{
		pr->precision = pr->width;
		pr->fl |= FL_PREC;
	}
	len = pf_itoa_base(pr, n, base, &str);
	(pr->fl & FL_ZERO) ? pr->fl &= ~FL_SPACE : 0;
	(pr->fl & FL_PREC) ? pr->fl &= ~FL_ZERO : 0;
	pr->padding = ft_max(pr->width - len, 0);
	ft_padding(pr, 0);
	pf_itoa_print_pref(pr, n, base);
	ft_buffer(pr, str, len);
	ft_padding(pr, 1);
	free(str);
}

void	pf_number_un(t_pr *pr, short base)
{
	uintmax_t		n;

	if (pr->fl & FL_LONG || pr->fl & FL_LONGL)
		n = (pr->fl & FL_LONG) ? ((intmax_t)va_arg(pr->list, unsigned long)) :
			((intmax_t)va_arg(pr->list, unsigned long long));
	else if (pr->fl & FL_SH || pr->fl & FL_SHS)
		n = (pr->fl & FL_SH) ? ((unsigned short)va_arg(pr->list, int)) :
			((unsigned char)va_arg(pr->list, int));
	else if (pr->fl & FL_INTMAX)
		n = (va_arg(pr->list, uintmax_t));
	else if (pr->fl & FL_SITE_T)
		n = ((uintmax_t)va_arg(pr->list, size_t));
	else
		n = (uintmax_t)va_arg(pr->list, unsigned int);
	pf_itoa_un(pr, n, base);
}
