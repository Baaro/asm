/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:10:28 by vsokolog          #+#    #+#             */
/*   Updated: 2018/03/14 16:10:35 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pars_flags(char **f, t_arg **arg)
{
	char	*c;

	c = NULL;
	while ((c = ft_strchr(FLAGS, **f)))
	{
		ARG.flags[c - FLAGS] = 1;
		(*f)++;
		c = NULL;
	}
}

static void	pars_width_bonus(char **f, va_list ap, t_arg **arg)
{
	if (**f == '*' && ft_isdigit(*(*f + 1)))
	{
		ARG.width = va_arg(ap, int);
		(*f)++;
		ARG.width = 0;
		while (**f && ft_isdigit(**f))
		{
			ARG.width = (ARG.width * 10) + ((**f) - '0');
			(*f)++;
		}
	}
	else
	{
		if ((ARG.width = va_arg(ap, int)) < 0)
		{
			ARG.width *= -1;
			ARG.flags[MINUS] = 1;
		}
		(*f)++;
	}
}

static void	pars_width(char **f, va_list ap, t_arg **arg)
{
	if (**f == '*')
		pars_width_bonus(f, ap, arg);
	else if (**f != '0' && ft_isdigit(**f))
	{
		while (**f && ft_isdigit(**f))
		{
			ARG.width = (ARG.width * 10) + ((**f) - '0');
			(*f)++;
		}
		if (**f == '*')
		{
			ARG.width = va_arg(ap, int);
			(*f)++;
		}
	}
}

static bool	pars_type(char **f, t_arg **arg)
{
	char *c;

	c = NULL;
	if ((c = ft_strchr(TYPES, **f)))
	{
		ARG.type = *c;
		c = NULL;
	}
	ARG.type = **f;
	return (1);
}

void		parsing(char **f, va_list ap, t_arg *arg)
{
	while (**f)
	{
		pars_flags(f, &arg);
		pars_width(f, ap, &arg);
		pars_precision(f, ap, &arg);
		pars_length(f, &arg);
		if (pars_type(f, &arg))
		{
			correct_flags(&arg);
			(*f)++;
			break ;
		}
		else
			break ;
	}
}
