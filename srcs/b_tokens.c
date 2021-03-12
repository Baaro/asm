/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tokens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:34:26 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:34:27 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			b_tokens_append(t_list **b_tokens, t_b_token *bt)
{
	ft_lstaddend(b_tokens, ft_lstnew(bt, sizeof(t_b_token)));
	ft_memdel((void**)&bt);
}

static t_b_token	*b_token_make(t_token *t, uint32_t sprv, uint32_t pprv)
{
	t_b_token	*bt;

	bt = ft_memalloc(sizeof(t_b_token));
	if (t->op)
	{
		bt->op_code = op_get_code(t->op);
		bt->op_template = (t_op_templ *)&g_op_template_tab[bt->op_code - 1];
		bt->codage = bt->op_template->codage;
		args_set(bt, t);
	}
	bt->pos = op_get_pos(pprv, sprv);
	bt->size = op_get_size(bt);
	bt->labels = ft_lstmap(t->labels, ft_lstget);
	return (bt);
}

void				b_tokens_del(t_list **b_tokens)
{
	t_list		*to_free;
	ssize_t		i;

	while (*b_tokens)
	{
		to_free = *b_tokens;
		*b_tokens = (*b_tokens)->next;
		ft_lstdel(&((t_b_token *)to_free->content)->labels, ft_lstelemfree);
		i = -1;
		while (++i < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)to_free->content)->args[i]
			&& ((t_b_token *)to_free->content)->args[i]->ref)
			{
				free(((t_b_token *)to_free->content)->args[i]->ref->name);
				free(((t_b_token *)to_free->content)->args[i]->ref);
			}
			free(((t_b_token *)to_free->content)->args[i]);
		}
		free(to_free->content);
		free(to_free);
	}
}

t_list				*b_tokens_make(t_list *tokens)
{
	uint32_t	pos;
	uint32_t	size;
	t_list		*b_tokens;
	t_b_token	*bt;

	pos = 0;
	size = 0;
	b_tokens = NULL;
	while (tokens)
	{
		bt = b_token_make((t_token *)tokens->content, pos, size);
		pos = bt->pos;
		size = bt->size;
		b_tokens_append(&b_tokens, bt);
		tokens = tokens->next;
	}
	return (b_tokens);
}
