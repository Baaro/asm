#include "asm.h"

void				append_bytecoded_tokens(t_list **b_tokens, t_bytecode *b_token)
{
	ft_lstaddend(b_tokens, ft_lstnew(b_token, sizeof(t_bytecode)));
	ft_memdel((void**)&b_token);
}

t_bytecode			*token_tbc(t_bytecode *b_prevtoken, t_token *token)
{
    t_bytecode	*b_token;

	b_token = ft_memalloc(sizeof(t_bytecode));
	b_token->instr_code = instr_get_code(token->instr);
	printf("instr_code: %d\n", b_token->instr_code);
    args_set(b_token, token);
	// b_token->pos = instr_get_pos(b_prevtoken);
    // b_token->size = instruction_get_size(b_token);
	b_token->labels = ft_lstmap(token->labels, ft_lstget);
	// free(b_token);
    return (b_token);
}

t_list				*tokens_tbc(t_list *tokens)
{
	t_list		*b_tokens;
	t_bytecode	*b_token;
	t_bytecode	*b_prevtoken;

	b_prevtoken = NULL;
	while (tokens)
	{
		b_token = token_tbc(b_prevtoken, (t_token *)tokens->content);
		// b_prevtoken = b_token;
		// append_bytecoded_tokens(&b_tokens, b_token);
		tokens = tokens->next;
	}
	return (b_tokens);
}
