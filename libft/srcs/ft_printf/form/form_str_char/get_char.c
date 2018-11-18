/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 11:45:03 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/21 11:45:04 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	output_char(char c, t_arg *arg)
{
	arg->len += write(1, &c, 1);
}

void		form_char(t_arg **arg, va_list ap)
{
	char	c;

	if (ft_strchr(TYPES, ARG.type))
		c = (unsigned char)va_arg(ap, int);
	else
		c = ARG.type;
	get_width_str_char(*arg, 1);
	if (ARG.flags[MINUS])
	{
		output_char(c, *arg);
		output(*arg, ARG.fm.w);
	}
	else
	{
		output(*arg, ARG.fm.w);
		output_char(c, *arg);
	}
}
