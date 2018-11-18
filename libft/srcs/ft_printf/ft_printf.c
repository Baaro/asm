/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:55:06 by vsokolog          #+#    #+#             */
/*   Updated: 2018/02/26 22:55:10 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_to_zero(t_arg *arg, short *i)
{
	*i = 0;
	arg->width = 0;
	arg->precision = -1;
	arg->l_size = 0;
	arg->type = '\0';
	arg->fm.w = NULL;
	arg->fm.p = NULL;
	arg->fm.n = NULL;
	arg->fm.flg = NULL;
}

static void	identify(char **f, t_arg *arg)
{
	char	*pos;

	if ((pos = ft_strchr(*f, '%')))
	{
		arg->len += write(1, *f, pos - *f);
		*f = pos + 1;
	}
	else
	{
		arg->len += write(1, *f, ft_strlen(*f));
		(*f) += ft_strlen(*f);
	}
}

int			ft_printf(const char *format, ...)
{
	char	*c_f;
	t_arg	arg;
	va_list	ap;
	short	i;

	i = 0;
	arg.len = 0;
	FLAGS_TO_ZERO(i);
	set_to_zero(&arg, &i);
	c_f = (char*)format;
	va_start(ap, format);
	while (*c_f)
	{
		identify(&c_f, &arg);
		parsing(&c_f, ap, &arg);
		if (arg.type == '\0')
			break ;
		form(ap, &arg);
		FLAGS_TO_ZERO(i);
		set_to_zero(&arg, &i);
	}
	va_end(ap);
	return (arg.len);
}
