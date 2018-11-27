#include "asm.h"

bool	is_whitespaces(const char c)
{
	return (c == '\t' || c == ' ');
}

size_t	shift_whitespaces(const char *str)
{
	size_t	counter;

	counter = 0;
	while (is_whitespaces(str[counter]))
		counter++;
	return (counter);
}

size_t	shift_chars(char c)
{
	if (c == LABEL_CHAR
	|| c == DIRECT_CHAR
	|| c == HEADER_DOT_CHAR
	|| c == STRING_QUOTES_CHAR
	|| c == SEPARATOR_CHAR)
		return (1);
	return (0);
}

void	valid_tail_of_string(char *line, size_t after_end_quotes, t_counter *counter)
{
	after_end_quotes += shift_whitespaces(line + after_end_quotes);
	if (line[after_end_quotes] != '\0'
	&& line[after_end_quotes] != COMMENT_CHAR
	&& line[after_end_quotes] != COMMENT_CHAR_ALTER)
	{
		counter->column = after_end_quotes + 1;
		lexical_errors(E_WRONG_TAIL_OF_STRING, line, counter);
	}
}

// bool	is_header_valid(char c, size_t h_cmds)
// {
// 	return (c != HEADER_DOT_CHAR && h_cmds == VALID);
// }



// bool	is_not_all_command_checked(char c, size_t h_cmds)
// {
// 	return (c != HEADER_DOT_CHAR && h_cmds != VALID);
// }

// bool	is_unknown_command(char c, size_t h_cmds)
// {
// 	return (c == HEADER_DOT_CHAR && h_cmds == VALID);
// }

