/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:19:34 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/06 13:19:37 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	big_integer(char **num, va_list ap, t_arg *arg)
{
	if (arg->l_size == l)
		*num = ft_itoabase(va_arg(ap, long), 10, arg);
	else if (arg->l_size == ll)
		*num = ft_itoabase(va_arg(ap, intmax_t), 10, arg);
	else if (arg->l_size == h)
		*num = ft_itoabase((unsigned short)va_arg(ap, long), 10, arg);
	else if (arg->l_size == hh)
		*num = ft_itoabase(va_arg(ap, int), 10, arg);
	else if (arg->l_size == j)
		*num = ft_itoabase(va_arg(ap, intmax_t), 10, arg);
	else if (arg->l_size == z)
		*num = ft_itoabase(va_arg(ap, size_t), 10, arg);
	else if (arg->l_size == t)
		*num = ft_itoabase(va_arg(ap, ptrdiff_t), 10, arg);
	else
		*num = ft_itoabase(va_arg(ap, long), 10, arg);
}

void		get_integer(char **num, va_list ap, t_arg *arg)
{
	if (arg->type == 'd' || arg->type == 'i')
	{
		if (arg->l_size == l)
			*num = ft_itoabase(va_arg(ap, long), 10, arg);
		else if (arg->l_size == ll)
			*num = ft_itoabase(va_arg(ap, intmax_t), 10, arg);
		else if (arg->l_size == h)
			*num = ft_itoabase((short)va_arg(ap, int), 10, arg);
		else if (arg->l_size == hh)
			*num = ft_itoabase((char)va_arg(ap, int), 10, arg);
		else if (arg->l_size == j)
			*num = ft_itoabase(va_arg(ap, intmax_t), 10, arg);
		else if (arg->l_size == z)
			*num = ft_itoabase((ptrdiff_t)va_arg(ap, size_t), 10, arg);
		else if (arg->l_size == t)
			*num = ft_itoabase(va_arg(ap, ptrdiff_t), 10, arg);
		else
			*num = ft_itoabase(va_arg(ap, int), 10, arg);
	}
	else
		big_integer(num, ap, arg);
}
