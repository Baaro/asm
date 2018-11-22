#include "asm.h"

bool	is_whitetspaces(const char c)
{
	return (c == '\t' || c == ' ');
}

size_t	shift_whitetspaces(const char *str)
{
	size_t	counter;

	counter = 0;
	while (is_whitetspaces(str[counter]))
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

bool	is_name_cmd(const char *line, t_counter *counter)
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

bool	is_comment_cmd(const char *line, t_counter *counter)
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

void	valid_tail_of_string(char *line, size_t after_end_quotes, t_counter *counter)
{
	after_end_quotes += shift_whitetspaces(line + after_end_quotes);
	if (line[after_end_quotes] != '\0'
	&& line[after_end_quotes] != COMMENT_CHAR
	&& line[after_end_quotes] != COMMENT_CHAR_ALTER)
	{
		ft_printf("errors(LEXICAL_ERROR, line, counter)\n");
		exit(1);
	}
}

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

bool	valid_comment(char *line, char **comment, t_counter *counter)
{
	size_t	comment_len;

	comment_len = 0;
	if (*comment)
	{
		ft_printf("errors(DOUBLE_NAME, line, counter)\n");
		exit(1);
	}
	counter->column += shift_whitetspaces(line + counter->column);
	if (line[counter->column] != STRING_QUOTES_CHAR)
	{
		ft_printf("erorrs(NO_BEGIN_QUOTES, line, counter)\n");
		exit(1);
	}
	counter->column += shift_chars(line[counter->column]);
	while (line[comment_len + counter->column])
	{
		if (comment_len > PROG_NAME_LENGTH)
		{
			ft_printf("errors(CHAMPION_NAME_TOO_LONG, line, counter)\n");
			exit(1);
		}
		if (line[comment_len + counter->column] == STRING_QUOTES_CHAR)
		{
			*comment = get_name(line, comment_len, counter);
			return (true);
		}
		if (line[(comment_len + 1) + counter->column] == '\0')
		{
			ft_printf("erorrs(NO_END_QUOTES, line, counter)\n");
			exit(1);
		}
		comment_len++;
	}
	return (false);
}

bool	valid_name(char *line, char **name, t_counter *counter)
{
	size_t	name_len;

	name_len = 0;
	if (*name)
		semantic_errors(DOUBLE_NAME, line, counter);
	counter->column += shift_whitetspaces(line + counter->column);
	if (line[counter->column] != STRING_QUOTES_CHAR)
		lexical_errors(NO_BEGIN_QUOTES, line, counter);
	counter->column += shift_chars(line[counter->column]);
	while (line[name_len + counter->column])
	{
		if (name_len > PROG_NAME_LENGTH)
		{
			ft_printf("errors(CHAMPION_NAME_TOO_LONG, line, counter)");
			exit(1);
		}
		if (line[name_len + counter->column] == STRING_QUOTES_CHAR)
		{
			*name = get_name(line, name_len, counter);
			return (true);
		}
		if (line[(name_len + 1) + counter->column] == '\0')
		{
			counter->column += name_len + 2;
			lexical_errors(NO_END_QUOTES, line, counter);
		}
		name_len++;
	}
	return (false);
}

bool	is_header_valid(char c, size_t h_cmds)
{
	return (c != HEADER_DOT_CHAR && h_cmds == VALID);
}

bool	is_endline_or_comment(char c)
{
	return (c == ENDLINE_CHAR || c == ENDSTRING_CHAR \
	|| c == COMMENT_CHAR || c == COMMENT_CHAR_ALTER);
}

bool	is_not_all_command_checked(char c, size_t h_cmds)
{
	return (c != HEADER_DOT_CHAR && h_cmds != VALID);
}

bool	is_unknown_command(char c, size_t h_cmds)
{
	return (c == HEADER_DOT_CHAR && h_cmds == VALID);
}

bool	is_dot_char(char c, size_t h_cmds)
{
	return (c == HEADER_DOT_CHAR && h_cmds != VALID);
}

void	valid_header(t_file *file, t_counter *counter) // test version
{
	size_t	h_cmds;

	h_cmds = 0;
	while (get_next_line(file->fd, &file->line) == 1)
	{
		counter->column = shift_whitetspaces(file->line);
		if (is_header_valid(file->line[counter->column], h_cmds))
		{
			ft_printf("line: %s\nchar: %c\n", file->line, file->line[counter->column]);
			break ;
		}
		if (is_endline_or_comment(file->line[counter->column]))
			continue ;
		if (is_not_all_command_checked(file->line[counter->column], h_cmds))
			syntactic_errors(NOT_ALL_COMMAND, file->line, counter);
		if (is_dot_char(file->line[counter->column], h_cmds))
		{
			if (is_name_cmd(file->line, counter))
				h_cmds += valid_name(file->line, &file->h_name, counter);
			else if (is_comment_cmd(file->line, counter))
				h_cmds += valid_comment(file->line, &file->h_comment, counter);
			else
				lexical_errors(UNMATCHED_COMMAND, file->line, counter);
		}
		counter->row++;
	}
	free(file->line);
}
