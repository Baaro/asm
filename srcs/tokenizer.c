#include "asm.h"

t_token	*tokenizer(t_file *file) // test version
{
	t_token		*head;
	t_counter	*counter;

	head = ft_memalloc(sizeof(t_token));
	counter = ft_memalloc(sizeof(t_counter));
	valid_header(file, counter);
	// tokenizing_instructions(file, head, counter);
	return (head);
}
