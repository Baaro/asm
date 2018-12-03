#include "asm.h"

static char	*get_comment(char *line, size_t comment_len, t_counter *counter)
{
	size_t	after_end_quotes;
	char	*comment;

	comment = NULL;
	after_end_quotes = counter->column + comment_len + 1;
	after_end_quotes += ft_strspn(line + after_end_quotes, DELIMS_CHARS);
	if (!line[after_end_quotes])
		comment = ft_strsub(line, counter->column, comment_len);
	else
	{
		counter->column = after_end_quotes + 1;
		lexical_errors(E_INVALID_SYMBOLS, line, counter);
	}
	return (comment);
}

static void	set_comment(t_file *file, t_counter *counter)
{
	size_t	comment_len;
	char	*comment;

	comment_len = -1;
	comment = NULL;
	while (++comment_len < COMMENT_LENGTH)
	{
		if (file->line[counter->column + comment_len] == QUOTES_CHAR)
		{
			comment = get_comment(file->line, comment_len, counter);
			ft_strncpy(file->hdr.comment, comment, comment_len);
			ft_strdel(&comment);
			return ;
		}
		if (!file->line[counter->column + comment_len + 1])
		{
			counter->column += comment_len + 2;
			lexical_errors(E_NO_END_QUOTES, file->line, counter);
		}
	}
	lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, file->line, counter);
}

bool		is_comment_cmd(char *str)
{
	return (ft_strnequ(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)));
}

void		valid_comment(t_file *file, t_counter *counter)
{
	if (!file->hdr.comment[0])
	{
		counter->column = ft_strlen(COMMENT_CMD_STRING);
		counter->column += ft_strspn(file->line + counter->column, DELIMS_CHARS);
		if (file->line[counter->column] == QUOTES_CHAR)
		{
			counter->column++;
			set_comment(file, counter);
		}
		else
			lexical_errors(E_NO_BEGIN_QUOTES, file->line, counter);
	}
	else
		semantic_errors(E_DOUBLE_COMMENT, file->line, counter);
}
