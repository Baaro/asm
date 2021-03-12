/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:41 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:42 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool				is_dir(char *arg_str)
{
	if (*arg_str == DIRECT_CHAR)
	{
		if (*(arg_str + 1) == LABEL_CHAR)
		{
			if (!is_label(arg_str + 2, ft_strlen(arg_str + 2)))
				linker_errors(E_UNKNOWN_REFERENCE, arg_str);
		}
		else if (!is_valid_val(arg_str + 1))
			semantic_errors(E_WRONG_ARGUMENT, arg_str, NULL);
		return (true);
	}
	return (false);
}

t_argument			*dir_get(uint8_t dir_size, char *arg_str)
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = DIR_CODE;
	if (*(arg_str + 1) == LABEL_CHAR)
	{
		arg->ref = ft_memalloc(sizeof(t_reference));
		arg->ref->len = ft_strlen(arg_str + 2);
		arg->ref->name = ft_strsub(arg_str, 2, arg->ref->len);
	}
	else
	{
		if (dir_size == USHORT)
			arg->val = ft_atoi32(arg_str + 1);
		else if (dir_size == UINT)
			arg->val = ft_atoi32(arg_str + 1);
	}
	arg->dir_size = dir_size;
	return (arg);
}
