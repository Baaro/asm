/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:22 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:23 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool		is_whitespaces(const char c)
{
	return (c == '\t' || c == ' ');
}

bool		is_valid_val(char *arg_str)
{
	if (*arg_str == '-')
		arg_str++;
	while (ft_isdigit(*arg_str))
	{
		if (*(arg_str + 1) == '\0')
			return (true);
		arg_str++;
	}
	return (false);
}

ssize_t		get_invalid_symbols(char *line, size_t len, char *valid_symbols)
{
	ssize_t	i;

	i = -1;
	while (line[++i] && i < (ssize_t)len)
	{
		if (!ft_strchr(valid_symbols, line[i]))
			return (i);
	}
	return (i == len ? -1 : i);
}

uint16_t	swap_uint16(uint16_t val)
{
	return ((val << 8) | (val >> 8));
}

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | (val >> 16));
}
