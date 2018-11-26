#include "asm.h"

static bool	is_name_cmd(const char *line, t_counter *counter)
{
	size_t	name_cmd_len;

	name_cmd_len = ft_strlen(NAME_CMD_STRING);
	if (ft_strnequ(line, NAME_CMD_STRING, name_cmd_len))
	{
		counter->column += name_cmd_len;
		return (true);
	}
	return (false);
}

static bool	is_comment_cmd(const char *line, t_counter *counter)
{
	size_t	comment_cmd_len;

	comment_cmd_len = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strnequ(line, COMMENT_CMD_STRING, comment_cmd_len))
	{
		counter->column += comment_cmd_len;
		return (true);
	}
	return (false);
}

static bool	valid_name(char *line, char **name, t_counter *counter)
{
	size_t	name_len;

	name_len = -1;
	if (*name)
		semantic_errors(E_DOUBLE_NAME, line, counter);
	counter->column += shift_whitespaces(line + counter->column);
	if (line[counter->column] != STRING_QUOTES_CHAR)
		lexical_errors(E_NO_BEGIN_QUOTES, line, counter);
	counter->column += shift_chars(line[counter->column]);
	while (line[++name_len + counter->column])
	{
		if (name_len > PROG_NAME_LENGTH)
			lexical_errors(E_CHAMPION_NAME_TOO_LONG, line, counter);
		if (line[name_len + counter->column] == STRING_QUOTES_CHAR)
		{
			*name = get_name(line, name_len, counter);
			return (true);
		}
		if (line[(name_len + 1) + counter->column] == '\0')
		{
			counter->column += name_len + 2;
			lexical_errors(E_NO_END_QUOTES, line, counter);
		}
	}
	return (false);
}

static bool	valid_comment(char *line, char **comment, t_counter *counter)
{
	size_t	comment_len;

	comment_len = -1;
	if (*comment)
		semantic_errors(E_DOUBLE_COMMENT, line, counter);
	counter->column += shift_whitespaces(line + counter->column);
	if (line[counter->column] != STRING_QUOTES_CHAR)
		lexical_errors(E_NO_BEGIN_QUOTES, line, counter);
	counter->column += shift_chars(line[counter->column]);
	while (line[++comment_len + counter->column])
	{
		if (comment_len > PROG_NAME_LENGTH)
			lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, line, counter);
		if (line[comment_len + counter->column] == STRING_QUOTES_CHAR)
		{
			*comment = get_name(line, comment_len, counter);
			return (true);
		}
		if (line[(comment_len + 1) + counter->column] == '\0')
		{
			counter->column += comment_len + 2;
			lexical_errors(E_NO_END_QUOTES, line, counter);
		}
	}
	return (false);
}

void	valid_commands(t_file *file, t_counter *counter, size_t *h_cmds)
{
	if (is_name_cmd(file->line, counter))
		*h_cmds += valid_name(file->line, &file->h_name, counter);
	else if (is_comment_cmd(file->line, counter))
		*h_cmds += valid_comment(file->line, &file->h_comment, counter);
	else
		semantic_errors(E_UNMATCHED_COMMAND, file->line, counter);
}
