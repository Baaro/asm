#include "asm.h"

// void			token_free(t_token *token) // does not work
// {
// 	ssize_t	i = -1;

// 	if (token->labels)
// 		ft_lstdel(&token->labels, ft_lstelemfree);
// 	// ft_memdel((void**)&token->labels);
// 	ft_strdel(&token->instr);
// 	while (++i < MAX_ARGS_NUMBER - 1)
// 	{
// 		if (token->args[i])
// 			ft_strdel(&token->args[i]);
// 	}
// 	ft_memdel((void**)&token);
// }

static void		token_append(t_list **token_head, t_token *token)
{
	ft_lstaddend(token_head, ft_lstnew(token, sizeof(t_token)));
	ft_memdel((void**)&token);
}

static t_token	*token_new(t_list *labels, char *fline, t_counter *c)
{
	t_token		*token;
	t_label		*label;

	token = ft_memalloc(sizeof(t_token));
	if ((label = label_get(fline, c)))	/* label with instr */
	{
		label_append(&labels, label);
		token->instr = instruction_get_str(fline, fline + label->len + 1, c);
	}
	else	/* instr without label */ 
		token->instr = instruction_get_str(fline, fline, c);
	token->labels = ft_lstmap(labels, ft_lstget);
	arguments_get_str(token, c);
	return (token);
}

t_list			*tokens_make(t_file *f, t_counter *c) // test version
{
	t_list		*tokens;
	t_list		*labels;
	t_token		*token;
	t_label		*label;

	labels = NULL;
	tokens = NULL;
	while ((file_get_line(f, c, false)) == 1)
	{
		if ((label = label_get_solo(f->line, c)))
			label_append(&labels, label);
		else
		{
			token = token_new(labels, f->line, c);
			token_append(&tokens, token);
			ft_lstdel(&labels, ft_lstelemfree);
		}
	}
    return (tokens);
}
