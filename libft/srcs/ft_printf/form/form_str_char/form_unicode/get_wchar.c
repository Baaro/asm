/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 17:21:18 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/30 17:21:20 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		output_wchar(t_arg *arg, char *c, int size)
{
	arg->len += write(1, c, size);
	ft_strdel(&c);
}

static void		left(char *c, int value, t_arg **arg)
{
	if (c && value > 0)
		output_wchar(*arg, c, ft_strlen(c));
	else
		output_wchar(*arg, c, 1);
	output(*arg, ARG.fm.w);
}

static void		right(char *c, int value, t_arg **arg)
{
	output(*arg, ARG.fm.w);
	if (c && value > 0)
		output_wchar(*arg, c, ft_strlen(c));
	else
		output_wchar(*arg, c, 1);
}

static char		*encode(int value, int size)
{
	char	*c;

	c = NULL;
	if (size <= 11 && MB_CUR_MAX >= 2)
	{
		c = ft_strnew(2);
		c[0] = 0b11000000 | (value >> 6);
		c[1] = (0b10000000 | value) & 0b10111111;
	}
	else if (size <= 16 && MB_CUR_MAX >= 3)
	{
		c = ft_strnew(3);
		c[0] = 0b11100000 | (value >> 12);
		c[1] = (0b11000000 | (value >> 6)) & 0b10111111;
		c[2] = (0b10000000 | value) & 0b10111111;
	}
	else if (MB_CUR_MAX >= 4)
	{
		c = ft_strnew(4);
		c[0] = 0b11110000 | (value >> 18);
		c[1] = (0b11100000 | (value >> 12));
		c[2] = (0b11000000 | (value >> 6)) & 0b10111111;
		c[3] = (0b10000000 | value) & 0b10111111;
	}
	return (c);
}

void			form_wchar(t_arg **arg, va_list ap)
{
	char	*c;
	int		size;
	int		value;

	value = va_arg(ap, int);
	size = count_bits(value);
	if (size <= 7 || (size <= 8 && MB_CUR_MAX == 1))
	{
		c = ft_strnew(1);
		c[0] = value;
	}
	else
		c = encode(value, size);
	if (!c)
		c = ft_strnew(0);
	get_width_str_char(*arg, ft_strlen(c));
	if (ARG.flags[MINUS])
		left(c, value, arg);
	else
		right(c, value, arg);
}
