/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_precision_num.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 15:27:34 by vsokolog          #+#    #+#             */
/*   Updated: 2018/05/03 15:27:35 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	size_flgs(t_arg arg)
{
	if (arg.flags[PLUS])
		return (1);
	else if ((arg.flags[HESH]
	&& (arg.type == 'x' || arg.type == 'X')) || (arg.type == 'p'))
		return (2);
	else if (arg.flags[HESH] && (arg.type == 'o' || arg.type == 'O'))
		return (1);
	else if (arg.flags[NEGATIVE])
		return (1);
	else if (arg.width && arg.flags[ZERO] && arg.flags[SPACE])
		return (1);
	return (0);
}

static void	ft_precision_num(char **prec, int size, t_arg arg)
{
	if (arg.type == 'p' || arg.type == 'x' || arg.type == 'd')
		size += size_flgs(arg);
	*prec = ft_memset(ft_strnew(size), '0', size);
}

static void	ft_width_num(char **width, int size, t_arg arg)
{
	if (size > 0 && arg.flags[ZERO] && arg.precision < 0
	&& !arg.flags[MINUS] && arg.type == '%')
		*width = ft_memset(ft_strnew(size), '0', size);
	else if (size > 0 && arg.flags[ZERO]
	&& (arg.precision < 0 || arg.precision == 0)
	&& !arg.flags[MINUS])
		*width = ft_memset(ft_strnew(size), '0', size);
	else
		*width = ft_memset(ft_strnew(size), ' ', size);
}

static void	precision_is_major(char **p, char **w, t_arg arg, int n)
{
	if (arg.type == '%')
		empty(p);
	else
		ft_precision_num(p, arg.precision - n, arg);
	empty(w);
}

void		get_width_precision_num(char **p, char **w, t_arg arg, int n)
{
	n += size_flgs(arg);
	if (arg.width > n && arg.width > arg.precision)
	{
		if (arg.precision >= n)
		{
			ft_precision_num(p, arg.precision - n, arg);
			ft_width_num(w, arg.width - arg.precision - size_flgs(arg), arg);
		}
		else
		{
			ft_width_num(w, arg.width - n, arg);
			empty(p);
		}
	}
	else if (arg.precision > n && arg.precision >= arg.width)
		precision_is_major(p, w, arg, n);
	else if (n >= arg.width && n >= arg.precision)
	{
		empty(p);
		empty(w);
	}
}
