/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ind.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:23 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:24 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool				is_ind(char *arg_str)
{
	if (*arg_str == LABEL_CHAR)
	{
		if (!is_label(arg_str + 1, ft_strlen(arg_str + 1)))
		{
			ft_printf("wrong ref: %s\n", arg_str);
			exit(1);
		}
		return (true);
	}
	else if (*arg_str == '-' || ft_isdigit(*arg_str))
	{
		if (!is_valid_val(arg_str))
			semantic_errors(E_WRONG_ARGUMENT, arg_str, NULL);
		return (true);
	}
	else if (ft_isalpha(*arg_str))
		semantic_errors(E_WRONG_ARGUMENT, arg_str, NULL);
	return (false);
}

t_argument			*ind_get(char *arg_str)
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = IND_CODE;
	if (*arg_str == LABEL_CHAR)
	{
		arg->ref = ft_memalloc(sizeof(t_reference));
		arg->ref->len = ft_strlen(arg_str + 1);
		arg->ref->name = ft_strsub(arg_str, 1, arg->ref->len);
	}
	else
		arg->val = ft_atoi32(arg_str);
	return (arg);
}
