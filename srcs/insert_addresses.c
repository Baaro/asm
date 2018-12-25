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

uint32_t	get_addresses(t_b_token *label, t_b_token *ref, ssize_t curr_arg)
{
	uint32_t val;

	val = 0;
	printf("lab_pos: %u ref_pos: %u\n", label->pos, ref->pos);
	if (ref->args[curr_arg]->code == IND_CODE)
		val = label->pos - ref->pos;
		// val = swap_uint16(label->pos - ref->pos);		
	else if (ref->args[curr_arg]->code == DIR_CODE)
	{
		if (ref->args[curr_arg]->dir_size == USHORT)
			val = label->pos - ref->pos;
			// val = swap_uint16(label->pos - ref->pos);
		else if (ref->args[curr_arg]->dir_size  == UINT)
			val = label->pos - ref->pos;
			// val = swap_uint32(label->pos - ref->pos);
	}
	return (val);
}

t_b_token		*get_label_pos(t_list *b_tokens, t_list *refs, ssize_t curr_arg)
{
	t_list		*tokens_labs;
	t_list		*labels;
	t_b_token	*label;
	char		*ref_name;
	bool		found;

	found = false;
	if (((t_b_token *)refs->content)->args[curr_arg]
	&& ((t_b_token *)refs->content)->args[curr_arg]->ref)
	{
		tokens_labs = b_tokens;
		while (tokens_labs)
		{
			labels = ((t_b_token *)tokens_labs->content)->labels;
			ref_name = ((t_b_token *)refs->content)->args[curr_arg]->ref->name;
			if (label_exists(labels, ref_name))
			{
				found = true;
				label = (t_b_token *)tokens_labs;
				break ;
			}
			tokens_labs = tokens_labs->next;
		}
		if (!found)
			printf("ERROR: UNKNWON REFERENCE:\n");
	}
	return (found ? label : NULL);
}

void	insert_addresses(t_list **b_tokens, uint32_t *size)
{
	ssize_t		curr_arg;
	t_list		*tokens_refs;
	t_b_token	*label_pos;

	// get ref
	//	find label with the same name
	//		if found
	// 			set value
	//		else
	//			error: no label with this name
	tokens_refs = *b_tokens;
	while (tokens_refs)
	{
		curr_arg = -1;
		while (++curr_arg < MAX_ARGS_NUMBER - 1)
		{
			if ((label_pos = get_label_pos(*b_tokens, tokens_refs, curr_arg)))
			{
				((t_b_token *)tokens_refs->content)->args[curr_arg]->val = get_addresses(label_pos, ((t_b_token *)tokens_refs->content), curr_arg);
				printf("val: %u\n", ((t_b_token *)tokens_refs->content)->args[curr_arg]->val);
			}
			// else
			// {
				// printf("ERROR: UNKNWON REFERENCE:\n");
				// if (((t_b_token *)tokens_refs->content)->args[curr_arg]->code == DIR_CODE)
					// printf("ERROR: UNKNWON REFERENCE: \"%c%c%s\"\n", DIRECT_CHAR, LABEL_CHAR, ((t_b_token *)tokens_refs->content)->args[curr_arg]->ref->name);
				// else if (((t_b_token *)tokens_refs->content)->args[curr_arg]->code == IND_CODE)
					// printf("ERROR: UNKNWON REFERENCE: \"%c%s\"\n", LABEL_CHAR, ((t_b_token *)tokens_refs->content)->args[curr_arg]->ref->name);
				// exit(EXIT_FAILURE);
			// }
		}
		*size += ((t_b_token*)tokens_refs->content)->size;
		tokens_refs = tokens_refs->next;
	}
}
