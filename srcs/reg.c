/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:40 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:42 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool		is_reg(char *arg)
{
	char	*copy_arg;
	size_t	arg_len;

	copy_arg = arg;
	arg_len = ft_strlen(copy_arg);
	if (*copy_arg == 'r' && arg_len >= 1 && arg_len <= 3)
	{
		++copy_arg;
		while (*copy_arg)
		{
			if (!(ft_isdigit(*copy_arg)))
			{
				ft_printf("ERROR: Wrong reg: %s\n", arg);
				exit(EXIT_FAILURE);
			}
			copy_arg++;
		}
	}
	else
		return (false);
	return (true);
}

t_argument	*reg_get(char *arg_str)
{
	t_argument	*arg;

	arg = ft_memalloc(sizeof(t_argument));
	arg->code = REG_CODE;
	arg->val = ft_atoi32(arg_str + 1);
	if (arg->val < 1 || arg->val > 99)
		semantic_errors(E_WRONG_ARGUMENT, arg_str, NULL);
	return (arg);
}
