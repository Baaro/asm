#include "asm.h"

size_t		get_currunet_column(t_counter *counter)
{
	return (counter->column + counter->begin_whitespaces); 
}

size_t		get_currunet_position(t_counter *counter)
{
	return (counter->column);
}

bool	is_whitespaces(const char c)
{
	return (c == '\t' || c == ' ');
}

// size_t	get_whitespaces(const char *str)
// {
// 	size_t	counter;

// 	counter = 0;
// 	while (is_whitespaces(str[counter]))
// 		counter++;
// 	return (counter);
// }

// size_t	shift_chars(char c)
// {
// 	if (c == LABEL_CHAR
// 	|| c == DIRECT_CHAR
// 	|| c == HEADER_DOT_CHAR
// 	|| c == QUOTES_CHAR
// 	|| c == SEPARATOR_CHAR)
// 		return (1);
// 	return (0);
// }

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

