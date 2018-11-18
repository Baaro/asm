/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_wstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:22:51 by vsokolog          #+#    #+#             */
/*   Updated: 2018/05/03 16:22:53 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fill_width_wstr(char **width, t_arg arg, int size)
{
	if (size > 0 && arg.flags[ZERO] && !arg.flags[MINUS])
		*width = ft_memset(ft_strnew(size), '0', size);
	else
		*width = ft_memset(ft_strnew(size), ' ', size);
}

void			get_width_wstr(t_arg *arg, int size)
{
	if (arg->width > size)
	{
		if (arg->precision > 0 && arg->precision <= size)
			fill_width_wstr(&arg->fm.w, *arg, arg->width - arg->precision);
		else
			fill_width_wstr(&arg->fm.w, *arg, arg->width - size);
	}
	else
		empty(&arg->fm.w);
}
