/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_addresses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 16:38:01 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 16:38:02 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	get_address(t_list *refs, t_list *b_tokens, ssize_t curr_arg)
{
	uint32_t	labpos;
	uint32_t	refpos;
	uint8_t		argcode;
	uint32_t	val;

	labpos = ((t_b_token *)b_tokens->content)->pos;
	refpos = ((t_b_token *)refs->content)->pos;
	argcode = ((t_b_token *)refs->content)->args[curr_arg]->code;
	if (argcode == IND_CODE)
		val = swap_uint16(labpos - refpos);
	else if (argcode == DIR_CODE)
	{
		if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == USHORT)
			val = swap_uint16(labpos - refpos);
		else if (((t_b_token *)refs->content)->args[curr_arg]->dir_size == UINT)
			val = swap_uint32(labpos - refpos);
	}
	((t_b_token *)refs->content)->args[curr_arg]->val = val;
}

static void	compute_address(t_list *refs, t_list *b_tokens, ssize_t curr_arg)
{
	char		*refname;
	char		*labname;
	t_list		*labels;

	while (b_tokens)
	{
		labels = ((t_b_token *)b_tokens->content)->labels;
		while (labels)
		{
			refname = ((t_b_token *)refs->content)->args[curr_arg]->ref->name;
			labname = ((t_label *)labels->content)->name;
			if (ft_strequ(refname, labname))
			{
				get_address(refs, b_tokens, curr_arg);
				return ;
			}
			labels = labels->next;
		}
		b_tokens = b_tokens->next;
	}
	linker_errors(((t_b_token *)refs->content)->args[curr_arg]->ref->name);
}

void		insert_addresses(t_list **b_tokens, uint32_t *size)
{
	ssize_t	curr_arg;
	t_list	*refs;

	refs = *b_tokens;
	while (refs)
	{
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)refs->content)->args[curr_arg]
			&& ((t_b_token *)refs->content)->args[curr_arg]->ref)
				compute_address(refs, *b_tokens, curr_arg);
		}
		*size += ((t_b_token*)refs->content)->size;
		refs = refs->next;
	}
}
