#include "asm.h"

char	*get_name(char *line, size_t name_len, t_counter *counter)
{
	char	*name;
	size_t	after_end_quotes;

	after_end_quotes = name_len + 1 + counter->column;
	valid_tail_of_string(line, after_end_quotes, counter);
	name = ft_strsub(line, counter->column, name_len);
	return (name);
}

char	*get_comment(char *line, size_t comment_len, t_counter *counter)
{
	char	*comment;
	size_t	after_end_quotes;

	after_end_quotes = comment_len + 1 + counter->column;
	valid_tail_of_string(line, after_end_quotes, counter);
	comment = ft_strsub(line, counter->column, comment_len);
	return (comment);
}
