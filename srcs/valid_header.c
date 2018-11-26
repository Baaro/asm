#include "asm.h"

static bool	is_dot_char(char c, size_t h_cmds)
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

static void	check_gnl_status(int gnl_status, t_file *file, t_counter *counter)
{
	if (gnl_status == 0)
		lexical_errors(E_IS_NOT_ENOUGH_DATA, file->name, counter);
	else if (gnl_status == -1)
		lexical_errors(E_WRONG_INPUT, file->line, counter);
}

void		valid_header(t_file *file, t_counter *counter)
{
	size_t	h_cmds;
	int 	gnl_status;

	h_cmds = 0;
	gnl_status = 0;
	while ((gnl_status = get_next_line(file->fd, &file->line) == 1))
	{
		counter->row++;
		counter->column = shift_whitespaces(file->line);
		file->data = append_data(file->data, file->line);
		if (is_endline_or_comment(file->line[counter->column]))
			continue ;
		if (!is_dot_char(file->line[counter->column], h_cmds))
		{
			if (h_cmds == VALID)
				break ;
			syntactic_errors(E_NOT_ALL_COMMAND, file->line, counter);
		}
		if (h_cmds != VALID)
			valid_commands(file, counter, &h_cmds);
		else
			semantic_errors(E_COMMAND_READ, file->line, counter);
	}
	check_gnl_status(gnl_status, file, counter);
}
