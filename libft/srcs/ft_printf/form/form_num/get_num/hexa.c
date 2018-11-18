/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:18:55 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/06 13:18:58 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*up(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

static void	low_hexa(char **num, va_list ap, t_arg *arg)
{
	if (arg->l_size == l)
		*num = ft_uns_itoabase((unsigned long)va_arg(ap, long), 16);
	else if (arg->l_size == ll)
		*num = ft_uns_itoabase((unsigned long long)va_arg(ap, long long), 16);
	else if (arg->l_size == hh)
		*num = ft_uns_itoabase((unsigned char)va_arg(ap, int), 16);
	else if (arg->l_size == h)
		*num = ft_uns_itoabase((unsigned short)va_arg(ap, int), 16);
	else if (arg->l_size == j)
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 16);
	else if (arg->l_size == z)
		*num = ft_uns_itoabase(va_arg(ap, size_t), 16);
	else if (arg->l_size == t)
		*num = ft_uns_itoabase((size_t)va_arg(ap, ptrdiff_t), 16);
	else
		*num = ft_uns_itoabase((unsigned int)va_arg(ap, int), 16);
}

void		get_hexa(char **num, va_list ap, t_arg *arg)
{
	if (arg->type == 'X')
	{
		if (arg->l_size == l)
			*num = up(ft_uns_itoabase((unsigned long)va_arg(ap, long), 16));
		else if (arg->l_size == ll)
			*num = up(ft_uns_itoabase((unsigned long long)
			va_arg(ap, long long), 16));
		else if (arg->l_size == hh)
			*num = up(ft_uns_itoabase((unsigned char)va_arg(ap, int), 16));
		else if (arg->l_size == h)
			*num = up(ft_uns_itoabase((unsigned short)va_arg(ap, int), 16));
		else if (arg->l_size == j)
			*num = up(ft_uns_itoabase(va_arg(ap, uintmax_t), 16));
		else if (arg->l_size == z)
			*num = up(ft_uns_itoabase(va_arg(ap, size_t), 16));
		else if (arg->l_size == t)
			*num = up(ft_uns_itoabase((size_t)va_arg(ap, ptrdiff_t), 16));
		else
			*num = up(ft_uns_itoabase((unsigned int)va_arg(ap, int), 16));
	}
	else
		low_hexa(num, ap, arg);
}
