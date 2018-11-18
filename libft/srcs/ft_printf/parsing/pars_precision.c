/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_precision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:49:57 by vsokolog          #+#    #+#             */
/*   Updated: 2018/05/03 20:49:58 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pars_p_bonus(char **f, va_list ap, t_arg **arg)
{
	if ((ARG.precision = va_arg(ap, int)) > 0)
		ABS(ARG.precision);
	(*f) = (*f + 2);
}

static void	pars_p_isdigit(char **f, t_arg **arg)
{
	(*f)++;
	ARG.precision = 0;
	if (*(*f) == '-')
	{
		ARG.flags[MINUS] = 1;
		(*f)++;
	}
	while (*f && ft_isdigit(**f))
	{
		ARG.precision = (ARG.precision * 10) + ((**f) - '0');
		(*f)++;
	}
	if (ARG.precision < 0)
	{
		ABS(ARG.precision);
		ARG.flags[MINUS] = 1;
	}
}

static void	pars_p_isndigit(char **f, t_arg **arg)
{
	ARG.precision = 0;
	(*f)++;
	if (*(*f + 1) == 0 && *(*f + 1) != '\0')
		(*f)++;
}

void		pars_precision(char **f, va_list ap, t_arg **arg)
{
	if (**f == '.' && *(*f + 1) == '*')
		pars_p_bonus(f, ap, arg);
	else if ((**f == '.' && (ft_isdigit(*(*f + 1)) || *(*f + 1) == '-')))
		pars_p_isdigit(f, arg);
	else if (**f == '.' && (!(ft_isdigit(*(*f + 1)) || *(*f + 1) == 0)))
		pars_p_isndigit(f, arg);
}
