/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_precision_str_char.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 12:03:45 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/21 12:03:46 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_width_str(char **width, t_arg arg, int size)
{
	if (size > 0 && arg.flags[ZERO] && !arg.flags[MINUS])
		*width = ft_memset(ft_strnew(size), '0', size);
	else
		*width = ft_memset(ft_strnew(size), ' ', size);
}

void		get_width_str_char(t_arg *arg, int l_src)
{
	if (arg->width > l_src)
	{
		if (arg->precision > 0 && arg->precision <= l_src)
			get_width_str(&arg->fm.w, *arg, arg->width - arg->precision);
		else
			get_width_str(&arg->fm.w, *arg, arg->width - l_src);
	}
	else
		empty(&arg->fm.w);
}
