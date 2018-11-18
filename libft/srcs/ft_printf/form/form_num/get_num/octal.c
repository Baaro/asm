/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:19:02 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/06 13:19:05 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	small_octal(char **num, va_list ap, t_arg *arg)
{
	if (arg->l_size == l)
		*num = ft_uns_itoabase(va_arg(ap, long), 8);
	else if (arg->l_size == ll)
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 8);
	else if (arg->l_size == hh)
		*num = ft_uns_itoabase((unsigned char)va_arg(ap, int), 8);
	else if (arg->l_size == h)
		*num = ft_uns_itoabase((unsigned short)va_arg(ap, int), 8);
	else if (arg->l_size == j)
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 8);
	else if (arg->l_size == z)
		*num = ft_uns_itoabase(va_arg(ap, size_t), 8);
	else if (arg->l_size == t)
		*num = ft_uns_itoabase((size_t)va_arg(ap, ptrdiff_t), 8);
	else
		*num = ft_uns_itoabase((unsigned int)va_arg(ap, int), 8);
}

void		get_octal(char **num, va_list ap, t_arg *arg)
{
	if (arg->type == 'O')
	{
		if (arg->l_size == l)
			*num = ft_uns_itoabase(va_arg(ap, long), 8);
		else if (arg->l_size == ll)
			*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 8);
		else if (arg->l_size == hh)
			*num = ft_uns_itoabase(va_arg(ap, long), 8);
		else if (arg->l_size == h)
			*num = ft_uns_itoabase((unsigned short)va_arg(ap, long), 8);
		else if (arg->l_size == j)
			*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 8);
		else if (arg->l_size == z)
			*num = ft_uns_itoabase(va_arg(ap, size_t), 8);
		else if (arg->l_size == t)
			*num = ft_uns_itoabase((size_t)va_arg(ap, ptrdiff_t), 8);
		else
			*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 8);
	}
	else
		small_octal(num, ap, arg);
}
