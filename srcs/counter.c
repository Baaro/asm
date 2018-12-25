/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:37 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:38 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		counter_clear(t_counter *c)
{
	int	args;

	args = c->args;
	ft_memset(c, 0, sizeof(t_counter));
	c->args = args;
}

void		counter_del(t_counter **c)
{
	ft_memdel((void **)c);
}

t_counter	*counter_new(void)
{
	return (ft_memalloc(sizeof(t_counter)));
}
