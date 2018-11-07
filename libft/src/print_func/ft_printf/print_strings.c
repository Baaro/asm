/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:50:02 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/03/18 18:50:04 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_wputchar(t_pr *pr, unsigned wc, short glen, short wlen)
{
	char	var[4];

	if (glen >= wlen && (unsigned short)wlen <= MB_CUR_MAX)
	{
		if (wlen == 1)
			var[0] = wc;
		else
		{
			if (wlen == 2)
				var[0] = (wc >> 6) | 0xC0;
			else
			{
				if (wlen == 3)
					var[0] = (wc >> 12) | 0xE0;
				else
				{
					var[0] = (wc >> 18) | 0xF0;
					var[1] = (wc >> 12 & 0x3F) | 0x80;
				}
				var[wlen - 2] = (wc >> 6 & 0x3F) | 0x80;
			}
			var[wlen - 1] = (wc & 0x3F) | 0x80;
		}
		ft_buffer(pr, var, wlen);
	}
}

void	pf_char(t_pr *pr, unsigned c)
{
	pr->n = ((pr->fl & FL_LONG) && (MB_CUR_MAX != 1)) ? ft_wcharlen(c) : 1;
	pr->padding = ft_max((pr->width - pr->n), 0);
	ft_padding(pr, 0);
	pf_wputchar(pr, c, pr->n, pr->n);
	ft_padding(pr, 1);
}

void	pf_putstr(t_pr *pr, unsigned *str)
{
	short		len;

	if (!str)
	{
		len = (pr->fl & FL_PREC) ? ft_min(6, pr->precision) : 6;
		pr->padding = ft_max((pr->width - len), 0);
		ft_padding(pr, 0);
		ft_buffer(pr, "(null)", len);
		ft_padding(pr, 1);
	}
	else
	{
		len = ft_strlen((char*)str);
		(pr->fl & FL_PREC) ? len = ft_min(pr->precision, len) : 0;
		pr->padding = ft_max(pr->width - len, 0);
		ft_padding(pr, 0);
		ft_buffer(pr, (char*)str, len);
		ft_padding(pr, 1);
	}
}

void	pf_wputstr(t_pr *pr, wchar_t *str)
{
	short		glen;
	short		wlen;
	size_t		f;
	wchar_t		w;

	if (!str)
		pf_putstr(pr, (unsigned*)str);
	else
	{
		glen = (pr->fl & FL_PREC) ? pr->precision : 0;
		f = (pr->fl & FL_PREC) ? 1 : 0;
		glen = (short)ft_wstrlen((unsigned*)str, f, glen);
		pr->padding = ft_max(pr->width - glen, 0);
		ft_padding(pr, 0);
		wlen = 0;
		while ((w = *str++) && (glen -= wlen) > 0)
		{
			wlen = ft_wcharlen(w);
			pf_wputchar(pr, w, glen, wlen);
		}
		ft_padding(pr, 1);
	}
}

void	pf_string(t_pr *pr)
{
	if (pr->fl & FL_LONG || pr->fl & FL_LONGL)
		pf_wputstr(pr, va_arg(pr->list, wchar_t*));
	else
		pf_putstr(pr, va_arg(pr->list, unsigned*));
}
