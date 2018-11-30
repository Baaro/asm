#include "asm.h"

// t_instruction	*get_instruction(t_file *file, t_counter *counter)
// {
// 	// if instruction in the line -> send to instruction detector
// 	// else use get_next_line while u will find the insturction
// }

// size_t			get_position(t_token *token)
// {

// }


// void			append_linker_labels(t_lists *lists, t_token *token)
// {
// 	if (token->labels)
// 		append_linker_label(lists->l_labels, token);
// }

// void			append_linker_references(t_lists *lists, t_token *token)
// {
// 	char	*current_reference;
// 	size_t	current_argument;

// 	current_argument = -1;
// 	while (++current_argument < MAX_ARGUMENTS)
// 	{
// 		current_reference = token->instruction.arguments[current_argument].reference;
// 		if (current_reference)
// 			append_linker_reference(lists->l_refs, token, current_reference);
// 	}
// }

void		ft_lstprint(t_list *elem)
{
	if (elem)
		ft_printf("%s\n", elem->content);
}

t_instruction	*new_instruction(char *line, t_counter *counter)
{
	t_instruction *instr;

	instr = ft_memalloc(sizeof(t_instruction));
	counter->column += get_whitespaces(line + counter->column);
	instr = get_instruction(line, counter);
	// instr->arguments = new_arguments(line, counter->column);
	return (instr);
}

t_token			*new_token(t_list *labels, char *line, t_counter *counter)
{
	t_token	*token;

	token = ft_memalloc(sizeof(t_token));
	token->labels = ft_lstmap(labels, ft_lstget); 
	ft_lstiter(token->labels, ft_lstprint);
	token->instruction = new_instruction(line, counter);
	line = NULL;
	counter = NULL;
	// token->position += token->instruction.size;
	// token->next = NULL;
	return (token);
}

void			tokenizer(t_file *file, t_lists *lists, t_counter *counter) // test version
{
	t_token		*token;

	token = NULL;
	while (file_get_line(file, counter) == 1)
	{
		if (is_label_without_instruction(file->line, counter))
			append_label(&lists->labels, new_label(file->line, counter));
		else
		{
			if (label_exists(file->line))
				append_label(&lists->labels, new_label(file->line, counter));
			token = new_token(lists->labels, file->line, counter);
			ft_lstdel(&lists->labels, ft_lstelemfree);
			// system("leaks asm");
			// break ;
			// append_linker_label(&lists->link_labels, token);
			// append_linker_refs(&lists->link_refs, token);
			// append_token(&lists->tokens, token);
			// ft_printf("FALSE: %s\n", file->line);
		}
	}
	// ft_lstiter(lists->labels, ft_lstprint);
}
