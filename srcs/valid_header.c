#include "asm.h"

bool	is_prog_name(const char *line, t_counter *counter)
{
	size_t	prog_name_len;

	prog_name_len = ft_strlen(NAME_CMD_STRING);
	if (ft_strnequ(line, NAME_CMD_STRING, prog_name_len))
	{
		counter->column += prog_name_len;
		return (true);
	}
	return (false);
}

bool	is_prog_comment(const char *line, t_counter *counter)
{
	size_t	prog_comment_len;

	prog_comment_len = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strnequ(line, COMMENT_CMD_STRING, prog_comment_len))
	{
		counter->column += prog_comment_len;
		return (true);
	}
	return (false);
}

void	valid_reminder_of_line(const char *line, t_counter *counter)
{
	
}

bool	valid_prog_string(char *line, char *cmd, t_counter *counter)
{
	size_t start;

	start = ++counter->column;
	while (ft_strchr(LABEL_CHARS, line[counter->column]))
	{
		if (line[counter->column + 1] == STRING_START_END_CHAR)
		{
			valid_reminder_of_line(line, counter);
			*cmd = ft_strsub(line, 0, counter->column - start);
			counter->column++;
			return (true);
		}
		counter->column++;
	}
	return (false);
}

bool	valid_prog_cmd(char *line, char **cmd, t_counter *counter)
{
	if (cmd)
	{
		if (*cmd)
			errors(DOUBLE_CMD);
		counter->column += shift_delims(line + counter->column);
		if (line[counter->column] == STRING_START_END_CHAR)
			if (valid_string(line, *cmd, counter))
				return (true);
		errors(INVALID_SYMBOLS, line, counter);
	}
	return (false);
}

void	valid_prog_header(t_file *file, t_counter *counter)
{
	size_t	h_cmds;

	h_cmds = 0;
	while (get_next_line(file->fd, &file->line) == 1)
	{
		counter->column = shift_delims(file->line);
		if (is_endline_or_comment(file->line[counter->column]))
			continue ;
		if (file->line[counter->column] != HEADER_DOT_CHAR && h_cmds != VALID)
			errors(NOT_ALL_CMD ,file->line, counter);
		if (file->line[counter->column] == HEADER_DOT_CHAR && h_cmds == VALID)
			errors(SYNTAX_ERROR, file->line, counter);
		if (file->line[counter->column] != HEADER_DOT_CHAR && h_cmds == VALID)
			break ;
		if (file->line[counter->column] == HEADER_DOT_CHAR && h_cmds != VALID)
		{
			if (is_prog_name(file->line, counter))
				h_cmds += valid_prog_cmd(file->line, &file->h_name, counter);
			else if (is_prog_comment(file->line, counter))
				h_cmds += valid_prog_cmd(file->line, &file->h_comment, counter);
			else
				errors(UNKNOWN_COMMAND, file->line, counter);
		}
		counter->row++;
	}
}
