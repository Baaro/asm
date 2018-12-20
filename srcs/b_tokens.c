#include "asm.h"

void				append_b_tokens(t_list **b_tokens, t_b_token *b_token)
{
	ft_lstaddend(b_tokens, ft_lstnew(b_token, sizeof(t_b_token)));
	free(b_token);
}

t_b_token			*b_token_make(t_token *token, uint32_t size_prev, uint32_t pos_prev)
{
    t_b_token	*b_token;

	b_token = ft_memalloc(sizeof(t_b_token));
	if (token->instr)
	{
		b_token->instr_code = instr_get_code(token->instr);
    	args_set(b_token, token);
	}
	b_token->pos = instr_get_pos(pos_prev, size_prev);
    b_token->size = instr_get_size(b_token);
	b_token->labels = ft_lstmap(token->labels, ft_lstget);
    return (b_token);
}

void				b_tokens_del(t_list **b_tokens)
{
	t_list		*to_free;
	t_list		*to_free_label;
	ssize_t		i;

	while (*b_tokens)
	{
		to_free = *b_tokens;
		to_free_label = ((t_b_token *)to_free->content)->labels;
		*b_tokens = (*b_tokens)->next;
		ft_lstdel(&((t_b_token *)to_free->content)->labels, ft_lstelemfree);
		i = -1;
		while (++i < MAX_ARGS_NUMBER - 1)
		{
			if (((t_b_token *)to_free->content)->args[i] != NULL)
			{
				if (((t_b_token *)to_free->content)->args[i] != NULL)
				{
					if (((t_b_token *)to_free->content)->args[i]->ref)
					{
						free(((t_b_token *)to_free->content)->args[i]->ref->name);
						free(((t_b_token *)to_free->content)->args[i]->ref);
					}
				}
				free(((t_b_token *)to_free->content)->args[i]);
			}
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
	t_b_token	*b_token;

	pos = 0;
	size = 0;
	b_tokens = NULL;
	while (tokens)
	{
		b_token = b_token_make((t_token *)tokens->content, pos, size);
		pos = b_token->pos;
		size = b_token->size;
		append_b_tokens(&b_tokens, b_token);
		tokens = tokens->next;
	}
	return (b_tokens);
}
