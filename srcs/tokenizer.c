#include "asm.h"

char			*get_label(t_file *file, t_counter *counter)
{
	char	*label;
	// if start with '.' char then -> lexical error
	label = NULL;
	if (is_label(file->line))
		label = get_label(file->line);
	else if (is_instruction(file->line))
		return (NULL);
	else if (is_garbrage(file->line));
		lexical_errors();
	return (label);
}

t_instruction	*get_instruction(t_file *file, t_counter *counter)
{
	// if instruction in the line -> send to instruction detector
	// else use get_next_line while u will find the insturction
}

size_t			get_position(t_token *token)
{

}

t_token			*new_token(t_file *file, t_counter *counter)
{
	t_token	*token;

	token = ft_memalloc(sizeof(t_token));
	token->labels = get_labels(file, counter);
	// token->instruction = get_instruction(file, counter);
	// token->position += token->instruction.size;
	// token->next = NULL;
	return (token);
}

// void			append_linker_labels(t_stacks *stacks, t_token *token)
// {
// 	if (token->labels)
// 		append_linker_label(stacks->l_labels, token);
// }

// void			append_linker_references(t_stacks *stacks, t_token *token)
// {
// 	char	*current_reference;
// 	size_t	current_argument;

// 	current_argument = -1;
// 	while (++current_argument < MAX_ARGUMENTS)
// 	{
// 		current_reference = token->instruction.arguments[current_argument].reference;
// 		if (current_reference)
// 			append_linker_reference(stacks->l_refs, token, current_reference);
// 	}
// }

void			tokenizer(t_file *file, t_stacks *stacks, t_counter *counter) // test version
{
	t_token *token;
	int		status;

	while ((status = file_get_line(file)) == 1)
	{
		counter->row++;
		counter->column = shift_whitespaces(file->line);
		if (is_endline_or_comment(file->line[counter->column]))
			continue ;
		token = new_token(file, counter);
		append_token(stacks->tokens, token);
		// append_linker_labels(stacks->l_labels, token);
		// append_linker_references(stacks->l_refs, token);
		// free(token);
	}
}
