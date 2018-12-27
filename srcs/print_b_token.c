/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_b_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 20:25:43 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/27 20:25:44 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_b_token_op(t_b_token *b_tkn)
{
	if (b_tkn->op_code)
	{
		if (b_tkn->op_code > 10)
			ft_printf("%22u", b_tkn->op_code);
		else
			ft_printf("%21u", b_tkn->op_code);
	}
}

static void	print_b_token_args_code(t_b_token *b_tkn)
{
	if (b_tkn->op_code)
	{
		if (b_tkn->args_code)
			ft_printf("%5u   ", b_tkn->args_code);
		else
			ft_printf("         ");
	}
}

static void	print_b_token_args_bytes(t_b_token *b_tkn)
{
	ssize_t		curr_arg;
	int32_t		val;

	val = 0;
	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (b_tkn->args[curr_arg])
		{
			val = b_tkn->args[curr_arg]->val;
			if (b_tkn->args[curr_arg]->code == REG_CODE)
				ft_printf("%-18d", b_tkn->args[curr_arg]->val);
			else if (b_tkn->args[curr_arg]->code == IND_CODE)
				print_bytes(val, false);
			else if (b_tkn->args[curr_arg]->code == DIR_CODE)
			{
				if (b_tkn->args[curr_arg]->dir_size == USHORT)
					print_bytes(val, false);
				else if (b_tkn->args[curr_arg]->dir_size == UINT)
					print_bytes(val, true);
			}
		}
	}
}

static void	print_b_token_args_val(t_b_token *b_tkn)
{
	ssize_t	curr_arg;

	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
	{
		if (b_tkn->args[curr_arg])
		{
			if (b_tkn->args[curr_arg]->code == REG_CODE)
				ft_printf("%-18d", b_tkn->args[curr_arg]->val);
			else if (b_tkn->args[curr_arg]->code == IND_CODE)
				ft_printf("%-18d", b_tkn->args[curr_arg]->val);
			else if (b_tkn->args[curr_arg]->code == DIR_CODE)
			{
				if (b_tkn->args[curr_arg]->dir_size == USHORT)
					ft_printf("%-18d", b_tkn->args[curr_arg]->val);
				else if (b_tkn->args[curr_arg]->dir_size == UINT)
					ft_printf("%-18d", b_tkn->args[curr_arg]->val);
			}
		}
	}
}

void		print_b_token(t_b_token *b_tkn)
{
	ssize_t i;

	i = -1;
	while (++i < 2)
	{
		print_b_token_op(b_tkn);
		print_b_token_args_code(b_tkn);
		if (i == 0)
			print_b_token_args_bytes(b_tkn);
		else
			print_b_token_args_val(b_tkn);
		ft_printf("\n");
	}
	ft_printf("\n");
}
