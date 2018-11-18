/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:24:07 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/05 18:24:08 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_num(char **num, va_list ap, t_arg *arg)
{
	if (arg->type == 'd' || arg->type == 'i' || arg->type == 'D')
		get_integer(num, ap, arg);
	else if (arg->type == 'o' || arg->type == 'O')
		get_octal(num, ap, arg);
	else if (arg->type == 'X' || arg->type == 'x')
		get_hexa(num, ap, arg);
	else if (arg->type == 'u' || arg->type == 'U')
		get_unsigned(num, ap, arg);
	else if (arg->type == 'p')
		*num = ft_uns_itoabase(va_arg(ap, uintmax_t), 16);
}

static void	get_flags(char **flg, t_arg arg, char *s_num)
{
	if ((!is_zero(s_num) && arg.flags[HESH]) || (arg.type == 'p'))
		ft_hesh(flg, arg);
	else if (arg.flags[PLUS] && !arg.flags[NEGATIVE])
	{
		*flg = ft_strnew(1);
		(*flg)[0] = '+';
	}
	else if (arg.flags[SPACE] && arg.type != '%'
	&& !arg.flags[NEGATIVE] && ((!arg.width || (arg.width && arg.flags[ZERO]))
	|| (arg.width < arg.precision)))
	{
		*flg = ft_strnew(1);
		(*flg)[0] = ' ';
	}
	else if (arg.flags[NEGATIVE])
	{
		*flg = ft_strnew(1);
		(*flg)[0] = '-';
	}
	else
		*flg = ft_strnew(0);
}

static void	correct_num(char **num, t_arg arg)
{
	if (is_zero(*num) && arg.precision >= 0 && !arg.flags[HESH])
	{
		if (*num)
			ft_strdel(num);
		*num = ft_strdup("");
	}
	else if (is_zero(*num) && arg.precision >= 0 && arg.flags[HESH]
	&& (arg.type == 'x' || arg.type == 'p'))
	{
		if (*num)
			ft_strdel(num);
		*num = ft_strdup("");
	}
}

void		form_nums(t_arg **arg, va_list ap)
{
	if (ARG.type == '%')
		ARG.fm.n = ft_strdup("%");
	else
		get_num(&ARG.fm.n, ap, *arg);
	get_flags(&ARG.fm.flg, ARG, ARG.fm.n);
	correct_num(&ARG.fm.n, ARG);
	get_width_precision_num(&ARG.fm.p, &ARG.fm.w, ARG, ft_strlen(ARG.fm.n));
	if (ARG.flags[ZERO] || ARG.flags[SPACE])
		output(*arg, output_by_order(ARG.fm.flg, ARG.fm.w, ARG.fm.p, ARG.fm.n));
	else if (ARG.flags[MINUS])
		output(*arg, output_by_order(ARG.fm.flg, ARG.fm.p, ARG.fm.n, ARG.fm.w));
	else
		output(*arg, output_by_order(ARG.fm.w, ARG.fm.flg, ARG.fm.p, ARG.fm.n));
}
