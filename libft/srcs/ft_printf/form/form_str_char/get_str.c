/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 11:42:23 by vsokolog          #+#    #+#             */
/*   Updated: 2018/04/21 11:42:24 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_str(char **dst, t_arg arg, va_list ap)
{
	bool	flag;
	char	*src;
	int		l_src;

	flag = 0;
	if (!(src = va_arg(ap, char*)))
	{
		if ((src = ft_strdup("(null)")))
			flag = 1;
	}
	l_src = ft_strlen(src);
	get_width_str_char(&arg, arg.precision < l_src
	&& arg.precision >= 0 ? arg.precision : l_src);
	if (arg.precision <= l_src && arg.precision >= 0)
		*dst = ft_strsub(src, 0, arg.precision);
	else
		*dst = ft_strsub(src, 0, l_src);
	if (arg.flags[MINUS])
		*dst = ft_strjoincl(*dst, arg.fm.w, 1);
	else
		*dst = ft_strjoincl(arg.fm.w, *dst, 1);
	if (flag)
		ft_strdel(&src);
}

void		form_str(t_arg **arg, va_list ap)
{
	char	*str;

	str = NULL;
	get_str(&str, ARG, ap);
	output(*arg, str);
}
