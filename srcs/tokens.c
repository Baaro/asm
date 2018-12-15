#include "asm.h"

static void		token_append(t_list **token_head, t_token *token)
{
	ft_lstaddend(token_head, ft_lstnew(token, sizeof(t_token)));
	ft_memdel((void**)&token);
}

static t_token	*token_new(t_list **curr_labels, t_list **all_labels, char *fline, t_counter *c)
{
	t_token		*token;
	t_label		*label;

	token = ft_memalloc(sizeof(t_token));
	if ((label = label_get(fline, c)))	/* label with instr */
	{
		if (!label_exists(*all_labels, label))
		{
			label_append(curr_labels, label);
			label_append(all_labels, label);
			// ft_memdel((void**)&label);
		}
		token->instr = instruction_get_str(fline, fline + label->len + 1, c);
	}
	else	/* instr without label */ 
		token->instr = instruction_get_str(fline, fline, c);
	token->labels = ft_lstmap(*curr_labels, ft_lstget);
	arguments_get_str(token, c);
	return (token);
}

void	tokens_del(t_list **tokens)
{
	t_list		*to_free;
	t_list		*to_free_label;

	while (*tokens)
	{
		to_free = *tokens;
		to_free_label = ((t_token *)to_free->content)->labels;
		*tokens = (*tokens)->next;
		while (to_free_label)
		{
			free(((t_label*)to_free_label->content)->name);
			to_free_label = to_free_label->next;
		}
		ft_lstdel(&((t_token *)to_free->content)->labels, ft_lstelemfree);// system("leaks asm");
		free(((t_token *)to_free->content)->instr);
		int i = -1;
		while (++i < MAX_ARGS_NUMBER - 1)
		{
			if (((t_token *)to_free->content)->args[i] != NULL)
				free(((t_token *)to_free->content)->args[i]);
		}
		free(to_free->content);
		free(to_free);
	}
}

void			label_print(t_list *label)
{
	printf("name: %s\n", ((t_label *)label->content)->name);
}

t_list			*tokens_make(t_file *f, t_counter *c) // test version
{
	t_list		*tokens;
	t_list		*curr_labels;
	t_list		*all_labels;
	t_token		*token;
	t_label		*label;

	curr_labels = NULL;
	all_labels = NULL;
	tokens = NULL;
	while ((file_get_line(f, c, false)) == 1)
	{
		if ((label = label_get_solo(f->line, c)))
		{
			if (!label_exists(all_labels, label))
			{
				ft_lstaddend(&curr_labels, ft_lstnew(label, sizeof(t_label)));
				ft_lstaddend(&all_labels, ft_lstnew(label, sizeof(t_label)));
				ft_memdel((void**)&label);
			}
		}
		else
		{
			token = token_new(&curr_labels, &all_labels, f->line, c);
			token_append(&tokens, token);
			ft_lstdel(&curr_labels, ft_lstelemfree);
		}
	}
	ft_lstiter(all_labels, label_print);
	// t_list	*to_free;
// 
	// to_free = all_labels;
	// while (to_free)
	// {
		// free((t_label*)all_labels->content);
		// to_free = to_free->next;
		// all_labels = to_free;
	// }
	// ft_lstdel(&to_free, ft_lstelemfree);// system("leaks asm");
	// free(all_labels);
    return (tokens);
}
