#include "asm.h"

static bool	is_dot_char(char c)
{
	return (c == HEADER_DOT_CHAR);
}

static bool	is_endline_or_comment(char c)
{
	if (c == ENDLINE_CHAR || c == ENDSTRING_CHAR)
		return (true);
	else if (c == COMMENT_CHAR || c == COMMENT_CHAR_ALTER)
		return (true);
	return (false);
}

static void	check_status(int gnl_status, t_file *file, t_counter *counter)
{
	if (gnl_status == 0)
		lexical_errors(E_IS_NOT_ENOUGH_DATA, file->name, counter);
	else if (gnl_status == -1)
		lexical_errors(E_WRONG_INPUT, file->line, counter);
}

void		valid_header(t_file *file, t_counter *counter)
{
	size_t	header_commands;
	int		status;

	header_commands = 0;
	while ((status = file_get_line(file)) == 1)
	{
		counter->row++;
		counter->column = shift_whitespaces(file->line);
		if (is_endline_or_comment(file->line[counter->column]))
			continue ;
		if (is_dot_char(file->line[counter->column]))
		{
			if ((header_commands += valid_commands(file, counter)) == VALID)
				return ;
		}
		else
			syntactic_errors(E_NOT_ALL_COMMAND, file->line, counter);
	}
	check_status(status, file, counter);
}
