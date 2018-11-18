/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:55:55 by vsokolog          #+#    #+#             */
/*   Updated: 2018/03/16 20:55:57 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	form_n(t_arg *arg, va_list ap)
{
	int	*n;

	n = (int*)va_arg(ap, void*);
	*n = arg->len;
}

void	form(va_list ap, t_arg *arg)
{
	if (arg->type == 'd' || arg->type == 'i'
	|| arg->type == 'D' || arg->type == 'o'
	|| arg->type == 'O' || arg->type == 'u'
	|| arg->type == 'U' || arg->type == 'X'
	|| arg->type == 'x' || arg->type == 'p' || arg->type == '%')
		form_nums(&arg, ap);
	else if ((arg->type == 's' && arg->l_size == l) || arg->type == 'S')
		form_wstr(&arg, ap);
	else if (arg->type == 's')
		form_str(&arg, ap);
	else if ((arg->type == 'c' && arg->l_size == l) || arg->type == 'C')
		form_wchar(&arg, ap);
	else if ((arg->type == 'c')
	|| (!ft_strchr(TYPES, arg->type) && arg->type != '\0'))
		form_char(&arg, ap);
	else if (arg->type == 'n')
		form_n(arg, ap);
}
