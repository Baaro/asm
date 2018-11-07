/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers_i.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:38:26 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/04/27 20:38:28 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *str)
{
	short	i;
	short	n;
	char	b;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	n = i;
	while (i > (n / 2))
	{
		b = *(str + n - i);
		*(str + n - i) = *(str + i - 1);
		*(str + i - 1) = b;
		i--;
	}
	return (str);
}

int		pf_itoa_base(t_pr *pr, uintmax_t n, short b, char **str)
{
	int		i;

	i = 0;
	if (pr->width > pr->precision)
		(*str) = (char*)ft_memalloc(sizeof(char) * ft_max(23, pr->width));
	else
		(*str) = (char*)ft_memalloc(sizeof(char) * ft_max(23, pr->precision));
	pr->c = 87 - ((pr->fl & FL_UPERCASE) >> 1);
	if (n == 0 && !(pr->fl & FL_PREC))
		(*str)[i++] = 48;
	while (n > 0)
	{
		(*str)[i++] = n % b + ((n % b < 10) ? 48 : pr->c);
		n /= b;
	}
	if (pr->fl & FL_PREC)
		while (i < pr->precision)
			(*str)[i++] = 48;
	(*str)[i] = '\0';
	(*str) = ft_strrev((*str));
	return (i);
}

void	pf_itoa(t_pr *pr, intmax_t n, short base)
{
	uintmax_t		m;
	int				len;
	char			*str;

	m = (n > 0) ? n : -n;
	(n < 0) ? pr->fl |= FL_PLUS : 0;
	len = 0;
	if (pr->fl & FL_SPACE || pr->fl & FL_PLUS)
		len++;
	len += pf_itoa_base(pr, m, base, &str);
	pr->padding = ft_max(pr->width - len, 0);
	((pr->fl & FL_ZERO) == 0) ? ft_padding(pr, 0) : 0;
	if (pr->fl & FL_PLUS)
		ft_buffer_char(pr, ((n < 0) ? '-' : '+'));
	(pr->fl & FL_SPACE && !(pr->fl & FL_PLUS)) ? ft_buffer_char(pr, ' ') : 0;
	(pr->fl & FL_ZERO) ? ft_padding(pr, 0) : 0;
	if (n < 0 || pr->fl & FL_SPACE || pr->fl & FL_PLUS)
		len--;
	ft_buffer(pr, str, len);
	free(str);
	ft_padding(pr, 1);
}

void	pf_number(t_pr *pr, short base)
{
	intmax_t		n;

	if (pr->fl & FL_LONG || pr->fl & FL_LONGL)
		n = (pr->fl & FL_LONG) ? ((intmax_t)va_arg(pr->list, long)) :
			((intmax_t)va_arg(pr->list, long long));
	else if (pr->fl & FL_SH || pr->fl & FL_SHS)
		n = (pr->fl & FL_SH) ? ((short)va_arg(pr->list, int)) :
			((char)va_arg(pr->list, int));
	else if (pr->fl & FL_INTMAX)
		n = (va_arg(pr->list, intmax_t));
	else if (pr->fl & FL_SITE_T)
		n = (va_arg(pr->list, size_t));
	else
		n = (va_arg(pr->list, int));
	if (ft_strchr("di", pr->c) && (pr->fl & FL_PREC))
		pr->fl &= ~FL_ZERO;
	pf_itoa(pr, n, base);
}
