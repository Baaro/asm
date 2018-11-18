/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 18:32:53 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/30 18:32:54 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*encode_second_bytes(int value, int size)
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

static char		*encode(int value)
{
	char	*c;
	int		size;

	size = count_bits(value);
	if (size <= 7 || (size <= 8 && MB_CUR_MAX == 1))
	{
		c = ft_strnew(1);
		c[0] = value;
	}
	else
		c = encode_second_bytes(value, size);
	if (!c)
		c = ft_strnew(0);
	return (c);
}

static void		get_wstr(char **wstr, t_arg arg, va_list ap)
{
	wchar_t	*ptr;
	char	*tmp;
	int		len;

	len = 0;
	if (!(ptr = va_arg(ap, wchar_t*)))
		*wstr = ft_strdup("(null)");
	else
	{
		*wstr = ft_strnew(wstrlen(ptr) * 4 + 1);
		while (*ptr)
		{
			tmp = encode(*ptr++);
			if ((len += ft_strlen(tmp)) <= arg.precision || arg.precision == -1)
				*wstr = ft_strcat(*wstr, tmp);
			free(tmp);
		}
		get_width_wstr(&arg, ft_strlen(*wstr));
		if (arg.flags[MINUS])
			*wstr = ft_strjoincl(*wstr, arg.fm.w, 1);
		else
			*wstr = ft_strjoincl(arg.fm.w, *wstr, 1);
	}
}

void			form_wstr(t_arg **arg, va_list ap)
{
	char	*wstr;

	wstr = NULL;
	get_wstr(&wstr, ARG, ap);
	output(*arg, wstr);
}
