/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:19:40 by vsokolog          #+#    #+#             */
/*   Updated: 2018/03/16 20:19:52 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	llhh(char **f, t_arg **arg)
{
	if (**f == 'l' && *(*f + 1) == 'l' && ARG.l_size <= ll)
	{
		ARG.l_size = ll;
		*f = (*f + 2);
	}
	else if (**f == 'h' && *(*f + 1) == 'h' && ARG.l_size <= hh)
	{
		ARG.l_size = hh;
		*f = (*f + 2);
	}
}

static void	lh(char **f, t_arg **arg)
{
	if (**f == 'l' && ARG.l_size <= l)
	{
		ARG.l_size = l;
		*f = (*f + 1);
	}
	else if (**f == 'h' && ARG.l_size <= h)
	{
		ARG.l_size = h;
		*f = (*f + 1);
	}
}

static void	jzt_bigl(char **f, t_arg **arg)
{
	if (**f == 'j' && ARG.l_size <= j)
	{
		ARG.l_size = j;
		*f = (*f + 1);
	}
	else if (**f == 'z' && ARG.l_size <= z)
	{
		ARG.l_size = z;
		*f = (*f + 1);
	}
	else if (**f == 't' && ARG.l_size <= t)
	{
		ARG.l_size = t;
		*f = (*f + 1);
	}
}

void		pars_length(char **f, t_arg **arg)
{
	llhh(f, arg);
	lh(f, arg);
	jzt_bigl(f, arg);
}
