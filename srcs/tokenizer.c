#include "asm.h"

bool	is_delims(const char c)
{
	return (c == '\t' || c == ' ');
}

bool	v_name(char **h_name, char *line, t_counter *counter)
{
	size_t	start;

	if (h_name)
	{
		if (*h_name)
			errors(DOUBLE_NAME);
		while (line[counter->column] && !is_delims(line[counter->column])
		|| line[counter->column] != STRING_CHAR))
		{
			if (line[counter->column] != NAME_CMD_STRING++)
				errors(INVALID_CMD, file->line, counter);
			counter->column++;
		}
		counter->column += shift_delims(line + counter->column)
		if (line[counter->column] == STRING_CHAR)
		{
			start = ++counter->column;
			while (line[counter->column] == STRING_CHAR)
			{
				if (!(ft_strchr(LABEL_CHARS, line[counter->column]))
					errors(INVALID_SYMBOLS);
				counter->column++;
			}
			name_found = true;
		}
	}
	return (false);
}

bool	v_cmmnt()
{
	if (comment_found == true)
		error();
	else if ((file->comment = get_comment()))
		comment_found = true;
}

size_t	shift_delims(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] == '\t' || str[counter] == ' ')
		counter++;
	return (counter);
}

void	valid_header(t_file *file, t_counter *counter)
{
	size_t	header;

	header = 0;
	while (get_next_line(file->fd, &file->line) == 1)
	{
		counter->column += shift_delims(file->line);
		if (file->line[counter->column] == ENDLINE_CHAR)
			continue ;
		if (file->line[counter->column] != HEADER_DOT_CHAR && header != VALID)
			errors(NO_NAME_OR_COMMENT ,file->line, counter);
		if (file->line[counter->column] == HEADER_DOT_CHAR && header == VALID)
			errors(INVALID_CMD, file->line, counter);
		if (file->line[counter->column] != HEADER_DOT_CHAR && header == VALID)
			break ;
		if (file->line[counter->column] == HEADER_DOT_CHAR && header != VALID)
		{
			if (is_name(file->line, counter))
				header += v_name(&file->h_name, file->line, counter);
			else if (is_comment(file->line, counter))
				header += v_cmmnt(&file->comment, file->line, counter);
			else
				errors(UNKNOWN_COMMAND);
		}
		counter->row++;
	}
}

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
