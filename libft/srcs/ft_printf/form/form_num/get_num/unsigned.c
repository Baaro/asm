/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:19:09 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/06 13:19:12 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	big_u(char **num, va_list ap, t_arg *arg)
{
	if (arg->l_size == l)
		*num = ft_uns_itoabase(va_arg(ap, long), 10);
	else if (arg->l_size == ll)
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 10);
	else if (arg->l_size == hh)
		*num = ft_uns_itoabase(va_arg(ap, unsigned long), 10);
	else if (arg->l_size == h)
		*num = ft_uns_itoabase(va_arg(ap, unsigned long), 10);
	else if (arg->l_size == j)
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 10);
	else if (arg->l_size == z)
		*num = ft_uns_itoabase(va_arg(ap, size_t), 10);
	else if (arg->l_size == t)
		*num = ft_uns_itoabase(va_arg(ap, ptrdiff_t), 10);
	else
		*num = ft_uns_itoabase(va_arg(ap, unsigned long), 10);
}

void	get_unsigned(char **num, va_list ap, t_arg *arg)
{
	if (arg->type == 'u')
	{
		if (arg->l_size == l)
			*num = ft_uns_itoabase(va_arg(ap, long), 10);
		else if (arg->l_size == ll)
			*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 10);
		else if (arg->l_size == hh)
			*num = ft_uns_itoabase((unsigned char)va_arg(ap, unsigned int), 10);
		else if (arg->l_size == h)
			*num = ft_uns_itoabase(
				(unsigned short)va_arg(ap, unsigned int), 10);
		else if (arg->l_size == j)
			*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 10);
		else if (arg->l_size == z)
			*num = ft_uns_itoabase(va_arg(ap, size_t), 10);
		else if (arg->l_size == t)
			*num = ft_uns_itoabase(va_arg(ap, ptrdiff_t), 10);
		else
			*num = ft_uns_itoabase(va_arg(ap, unsigned int), 10);
	}
	else
		big_u(num, ap, arg);
}
