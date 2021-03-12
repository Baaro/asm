/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 14:35:46 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/25 14:35:48 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		token_append(t_list **token_head, t_token *token)
{
	ft_lstaddend(token_head, ft_lstnew(token, sizeof(t_token)));
	ft_memdel((void**)&token);
}

static void		token_null(t_list **curr_labs, t_list **all_labs, t_list **tkns)
{
	t_token *token;

	token = NULL;
	if (*curr_labs)
	{
		token = ft_memalloc(sizeof(t_token));
		token->labels = ft_lstmap(*curr_labs, ft_lstget);
		token_append(tkns, token);
	}
	ft_lstdel(curr_labs, ft_lstelemfree);
	ft_lstdel(all_labs, ft_lstelemfree);
}

void			tokens_del(t_list **tkns)
{
	t_list		*to_free;
	t_list		*to_free_label;
	ssize_t		i;

	while (*tkns)
	{
		to_free = *tkns;
		to_free_label = ((t_token *)to_free->content)->labels;
		*tkns = (*tkns)->next;
		while (to_free_label)
		{
			free(((t_label*)to_free_label->content)->name);
			to_free_label = to_free_label->next;
		}
		ft_lstdel(&((t_token *)to_free->content)->labels, ft_lstelemfree);
		free(((t_token *)to_free->content)->op);
		free(((t_token *)to_free->content)->counter);
		i = -1;
		while (++i < MAX_ARGS_NUMBER - 1)
			if (((t_token *)to_free->content)->args[i] != NULL)
				free(((t_token *)to_free->content)->args[i]);
		free(to_free->content);
		free(to_free);
	}
}

static t_token	*token_new(t_list **cls, t_list **als, char *fl, t_counter *c)
{
	t_token		*token;
	t_label		*label;

	token = ft_memalloc(sizeof(t_token));
	token->counter = counter_new();
	token->counter->column = c->column;
	token->counter->row = c->row;
	if ((label = label_get(fl, c)))
	{
		if (!label_exists(*als, label->name))
			label_append(cls, als, label);
		else
			free(label->name);
		token->op = op_get_str(fl + label->len + 1, c);
		ft_memdel((void**)&label);
	}
	else
		token->op = op_get_str(fl, c);
	token->labels = ft_lstmap(*cls, ft_lstget);
	args_get_strs(token, c);
	return (token);
}

t_list			*tokens_make(t_file *f, t_counter *c)
{
	t_list		*tkns;
	t_list		*all_labs;
	t_list		*curr_labs;
	t_token		*t;
	t_label		*l;

	lists_to_null(&tkns, &all_labs, &curr_labs);
	while ((file_get_line(f, c, false)) == 1)
	{
		f->line = ft_strretrim(f->line);
		if ((l = label_get_solo(f->line, c)))
		{
			label_append(&curr_labs, &all_labs, l);
			ft_memdel((void**)&l);
		}
		else
		{
			t = token_new(&curr_labs, &all_labs, f->line, c);
			token_append(&tkns, t);
			ft_lstdel(&curr_labs, ft_lstelemfree);
		}
	}
	token_null(&curr_labs, &all_labs, &tkns);
	return (tkns);
}
