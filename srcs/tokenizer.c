#include "asm.h"

bool	is_delims(const char c)
{
	return (c == '\t' || c == ' ');
}

size_t	shift_delims(const char *str)
{
	size_t	counter;

	counter = 0;
	while (is_delims(str[counter]))
		counter++;
	return (counter);
}

t_token	*tokenizer(t_file *file) // test version
{
	t_token		*head;
	t_counter	*counter;

	head = ft_memalloc(sizeof(t_token));
	counter = ft_memalloc(sizeof(t_counter));
	valid_prog_header(file, counter);
	// tokenizing_instructions(file, head, counter);
	return (head);
}
