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

void		lists_to_null(t_list **first, t_list **second, t_list **third)
{
	*first = NULL;
	*second = NULL;
	*third = NULL;
}

ssize_t		get_invalid_symbols(char *line, size_t len, char *valid_smbls)
{
	ssize_t	i;

	i = -1;
	if (len == 0)
		if (!ft_strchr(valid_smbls, line[len]))
			return (len);
	while (line[++i] && i < (ssize_t)len)
	{
		if (!ft_strchr(valid_smbls, line[i]))
			return (i);
	}
	return ((size_t)i == len ? -1 : i);
}

void		print_bytes(int32_t val, bool four)
{
	if (four)
	{
		ft_printf("%-4d", ((val >> 24) & 0xFF));
		ft_printf("%-4d", ((val >> 16) & 0xFF));
		ft_printf("%-4d", ((val >> 8) & 0xFF));
		ft_printf("%-6d", (val & 0xFF));
	}
	else
	{
		ft_printf("%-4d", ((val >> 8) & 0xFF));
		ft_printf("%-14d", (val & 0xFF));
	}
}
