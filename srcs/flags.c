/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:15 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:16 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static bool	is_flag(const char *flag)
{
	return (*flag == '-' && *(flag + 2) == '\0');
}

static bool	is_flag_a(const char *flag)
{
	return (*flag == '-' && *(flag + 1) == 'a' && *(flag + 2) == '\0');
}

uint8_t		flags_get(int *ac, char ***av, t_counter *c)
{
	uint8_t flags;

	flags = 0;
	c->args = 1;
	while (c->args < *ac && is_flag((*av)[c->args]))
	{
		if (is_flag_a((*av)[c->args]))
			flags |= FLAG_A;
		c->args++;
	}
	return (flags);
}
