/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 20:25:48 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/27 20:25:49 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_pos_size(uint32_t pos, uint32_t size, bool op)
{
	if (op)
		ft_printf("%-5zu(%-3zu) :        ", pos, size);
	else
		ft_printf("%-11zu:", pos);
}

static void	print_token_labels(t_list *labels, uint32_t pos, uint32_t size)
{
	while (labels)
	{
		print_pos_size(pos, size, false);
		ft_printf("\t%s:\n", ((t_label *)labels->content)->name);
		labels = labels->next;
	}
}

static void	print_token_op(t_token *tkn, uint32_t pos, uint32_t size)
{
	if (tkn->op)
	{
		print_pos_size(pos, size, true);
		ft_printf("%-10s", tkn->op);
	}
}

static void	print_token_args(t_token *tkn)
{
	ssize_t	curr_arg;

	curr_arg = -1;
	while (++curr_arg < MAX_ARGS_NUMBER - 1)
		if (tkn->args[curr_arg])
			ft_printf("%-18s", tkn->args[curr_arg]);
	if (tkn->op)
		ft_printf("\n");
}

void		print_token(t_token *tkn, uint32_t pos, uint32_t size)
{
	print_token_labels(tkn->labels, pos, size);
	if (tkn->op)
	{
		print_token_op(tkn, pos, size);
		print_token_args(tkn);
	}
}
