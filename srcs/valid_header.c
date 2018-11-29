#include "asm.h"

static bool	is_dot_char(char *c)
{
	return (*c == HEADER_DOT_CHAR);
}

static void		valid_commands(t_file *file, t_counter *counter)
{
	if (is_name_cmd(file->line))
		valid_name(file, counter);
	else if (is_comment_cmd(file->line))
		valid_comment(file, counter);
	else
		semantic_errors(E_UNMATCHED_COMMAND, file->line, counter);
}

void		valid_header(t_file *file, t_counter *counter)
{
	size_t	header_commands;
	int		status;

	header_commands = 0;
	while ((status = file_get_line(file, counter)) == 1)
	{
		if (is_dot_char(file->line))
		{
			valid_commands(file, counter);
			if (++header_commands == VALID)
				return ;
		}
		else
			syntactic_errors(E_NOT_ALL_COMMAND, file->line, counter);
	}
	if (status == 0)
		lexical_errors(E_IS_NOT_ENOUGH_DATA, file->line, counter);
	else if (status == -1)
		lexical_errors(E_WRONG_INPUT, file->line, counter);
}
