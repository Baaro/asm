// #include "asm.h"

// // char			*get_label(t_file *file, t_counter *counter)
// // {
// // 	// if start with '.' char then -> lexical error
// // }

// // t_instruction	*get_instruction(t_file *file, t_counter *counter)
// // {
// // 	// if instruction in the line -> send to instruction detector
// // 	// else use get_next_line while u will find the insturction
// // }

// // size_t			get_position(t_token *token)
// // {

// // }

// // t_token			*new_token(t_file *file, t_counter *counter)
// // {
// // 	t_token	*token;

// // 	token = ft_memalloc(sizeof(t_token));
// // 	token->labels = get_labels(file, counter);
// // 	// token->instruction = get_instruction(file, counter);
// // 	// token->position += token->instruction.size;
// // 	// token->next = NULL;
// // 	return (token);
// // }

// // void			append_linker_labels(t_stacks *stacks, t_token *token)
// // {
// // 	if (token->labels)
// // 		append_linker_label(stacks->l_labels, token);
// // }

// // void			append_linker_references(t_stacks *stacks, t_token *token)
// // {
// // 	char	*current_reference;
// // 	size_t	current_argument;

// // 	current_argument = -1;
// // 	while (++current_argument < MAX_ARGUMENTS)
// // 	{
// // 		current_reference = token->instruction.arguments[current_argument].reference;
// // 		if (current_reference)
// // 			append_linker_reference(stacks->l_refs, token, current_reference);
// // 	}
// // }

// bool	is_label_char(char c)
// {
// 	return (c == LABEL_CHAR);
// }

// bool	is_invalid_symbols(char *line, size_t label_len)
// {
// 	size_t	label_counter;

// 	label_counter = 0;
// 	while (label_counter < label_len)
// 	{
// 		if (!(ft_strchr(LABEL_CHARS, line[label_counter])))
// 			return (true);
// 		label_counter++;
// 	}
// 	return (false);
// }

// bool	label_without_instruction(char *line, t_counter *counter)
// {
// 	size_t	label_counter;

// 	label_counter = 0;
// 	while (true)
// 	{
// 		if (line[label_counter] == '\0' || is_whitespaces(line[label_counter + 1]))
// 			return (false);
// 		if (is_label_char(line[label_counter]))
// 			break ;
// 		label_counter++;
// 	}
// 	if (is_invalid_symbols(line, label_counter))
// 	{
// 		counter->column = label_counter;
// 		semantic_errors(E_SEMANTIC_ERROR, line, counter);
// 	}
// 	counter->column += label_counter;
// 	return (true);
// }

// void	tokenizer(t_file *file, t_stacks *stacks, t_counter *counter) // test version
// {
// 	t_token	*token_head;
// 	t_label	*label_head;

// 	while (file_get_line(file, counter) == 1)
// 	{
// 		if (label_without_instruction(file->line, counter))
// 			ft_printf("TRUE: %s\n", file->line);
// 		else
// 			ft_printf("FALSE: %s\n", file->line);
// 			// append_label(label_head, new_label(file->line, counter));
// 		// else
// 		// {
// 			// if (label_with_instruction())
// 				// append_label(label_head, new_label(file->line, counter));
// 			// append_token(token_head, new_token(file, counter, label_head));
// 			// append_linker_labels(stacks->l_labels, token);
// 			// append_linker_references(stacks->l_refs, token);
// 		// }
// 	}
// }
