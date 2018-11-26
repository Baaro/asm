#include "asm.h"

// t_token	*get_token(t_file *file, t_counter *counter)
// {
// 	char		*label;
// 	char		*instraction;
// 	t_token 	*token;

// 	label = get_label(file->line);
// 	instraction = get_instraction(file->line);
// 	token = new_token(instraction, label);
// 	return (token);
// }

// void	tokenizing_instructions(t_file *file, t_token *head, t_counter *counter)
// {
// 	t_token		*token;

// 	if (!(token = get_token(file, counter)))
// 		return ;
// 	append_token(head, token);
// 	clear_token(&token);
// 	get_next_line(file->fd, &file->line);
// 	tokenizing_instructions(file, head, counter);
// }

t_token	*tokenizer(t_file *file) // test version
{
	t_token		*head;
	t_counter	*counter;

	head = ft_memalloc(sizeof(t_token));
	counter = ft_memalloc(sizeof(t_counter));
	valid_header(file, counter);
	ft_printf("data: \n%s", file->data);
	// tokenizing_instructions(file, head, counter);
	return (head);
}
