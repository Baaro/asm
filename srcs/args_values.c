/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:38:49 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:38:50 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_argument	*arg_get(t_b_token *bt, t_token *t, ssize_t curr_arg)
{
	t_argument	*arg;

	if (is_reg(t->args[curr_arg]))
		arg = reg_get(t->args[curr_arg]);
	else if (is_dir(t->args[curr_arg]))
		arg = dir_get(bt->op_template->dir_size, t->args[curr_arg]);
	else if (is_ind(t->args[curr_arg]))
		arg = ind_get(t->args[curr_arg]);
	else
	{
		ft_printf("Wrong argument for [%s]!\n", bt->op_template->name);
		exit(EXIT_FAILURE);
	}
	return (arg);
}

void				arg_valid(t_b_token *bt, ssize_t curr_arg)
{
	uint8_t arg_type;

	arg_type = 0;
	if (bt->args[curr_arg]->code == REG_CODE)
		arg_type = T_REG;
	else if (bt->args[curr_arg]->code == DIR_CODE)
		arg_type = T_DIR;
	else if (bt->args[curr_arg]->code == IND_CODE)
		arg_type = T_IND;
	if (bt->op_template->args[curr_arg] & arg_type)
		return ;
	else
	{
		ft_printf("Wrong argument for [%s]!\n", bt->op_template->name);
		exit(EXIT_FAILURE);
	}
}

void				args_set(t_b_token *bt, t_token *t)
{
	uint8_t		shift;
	ssize_t		curr_arg;

	shift = 6;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER)
	{
		if (bt->op_template->args[curr_arg])
		{
			if (t->args[curr_arg])
			{
				bt->args[curr_arg] = arg_get(bt, t, curr_arg);
				arg_valid(bt, curr_arg);
				if (bt->op_template->codage)
				{
					bt->args_code |= bt->args[curr_arg]->code << shift;
					shift -= 2;
				}
			}
			else
				semantic_errors(E_WRONG_ARGUMENT, bt->op_template->name, NULL);
		}
		else if (t->args[curr_arg])
			semantic_errors(E_WRONG_ARGUMENT, bt->op_template->name, NULL);
	}
}
