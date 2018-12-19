#include "asm.h"

void				append_b_tokens(t_list **b_tokens, t_b_token *b_token)
{
	ft_lstaddend(b_tokens, ft_lstnew(b_token, sizeof(t_b_token)));
	free(b_token);
}

t_b_token			*b_token_make(t_b_token *b_prevtoken, t_token *token)
{
    t_b_token	*b_token;

	b_token = ft_memalloc(sizeof(t_b_token));
	b_token->instr_code = instr_get_code(token->instr);
    args_set(b_token, token);
	b_token->pos = instr_get_pos(b_prevtoken);
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
					free(((t_b_token *)to_free->content)->args[i]->ref.name);
				free(((t_b_token *)to_free->content)->args[i]);
			}
		}
		free(to_free->content);
		free(to_free);
	}
}

t_list				*b_tokens_make(t_list *tokens)
{
	t_list		*b_tokens;
	t_b_token	*b_token;
	t_b_token	*b_prevtoken;

	b_tokens = NULL;
	b_prevtoken = NULL;
	while (tokens)
	{
		b_token = b_token_make(b_prevtoken, (t_token *)tokens->content);
		b_prevtoken = b_token;
		append_b_tokens(&b_tokens, b_token);
		tokens = tokens->next;
	}
	return (b_tokens);
}
