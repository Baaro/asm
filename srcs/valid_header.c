#include "asm.h"

static bool	is_dot_char(char *c)
{
	return (*c == HEADER_DOT_CHAR);
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
			if ((header_commands += valid_commands(file, counter)) == VALID)
				return ;
		}
		else
			syntactic_errors(E_NOT_ALL_COMMAND, file->line, counter);
	}
	if (status == 0)
		lexical_errors(E_IS_NOT_ENOUGH_DATA, file->name, counter);
	else if (status == -1)
		lexical_errors(E_WRONG_INPUT, file->line, counter);
}
