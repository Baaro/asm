#include "asm.h"

static char	*comment_str_get(char *line, size_t comment_len, t_counter *c)
{
	size_t	after_end_quotes;
	char	*comment;

	comment = NULL;
	after_end_quotes = c->column + comment_len + 1;
	after_end_quotes += ft_strspn(line + after_end_quotes, DELIMS_CHARS);
	if (!line[after_end_quotes])
		comment = ft_strsub(line, c->column, comment_len);
	else
	{
		c->column = after_end_quotes + 1;
		lexical_errors(E_INVALID_SYMBOLS, line, c);
	}
	return (comment);
}

static void	comment_set(t_header *h, char *line, size_t maxcmdlen, t_counter *c)
{
	size_t	command_len;
	char	*comment;

	comment_len = -1;
	comment = NULL;
	while (++comment_len < max_str_len)
	{
		if (line[c->column + comment_len] == QUOTES_CHAR)
		{
			comment = get_comment(line, comment_len, c);
			ft_strncpy(h->comment, comment, comment_len);
			ft_strdel(&comment);
			return ;
		}
		if (!line[c->column + comment_len + 1])
		{
			c->column += comment_len + 2;
			lexical_errors(E_NO_END_QUOTES, line, c);
		}
	}
	lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, line, c);
}

bool		is_comment_cmd(char *str)
{
	return (ft_strnequ(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)));
}

void		comment_get(t_header *h, char *line, bool choose_command, t_counter *c)
{
	size_t	max_str_len;

	if (choose_command)
	{
		if (!h->prog_name[0])
		{
			c->column = ft_strlen(NAME_CMD_STRING);
			c->column += ft_strspn(line + c->column, DELIMS_CHARS);
			if (line[c->column] == QUOTES_CHAR)
			{
				c->column++;
				name_str_set(h, line, c);
			}
			else
				lexical_errors(E_NO_BEGIN_QUOTES, line, c);
		}
		else
			semantic_errors(E_DOUBLE_NAME, line, c);
	}
	else
				if (!h->prog_name[0])
		{
			c->column = ft_strlen(NAME_CMD_STRING);
			c->column += ft_strspn(line + c->column, DELIMS_CHARS);
			if (line[c->column] == QUOTES_CHAR)
			{
				c->column++;
				name_str_set(h, line, c);
			}
			else
				lexical_errors(E_NO_BEGIN_QUOTES, line, c);
		}
		else
			semantic_errors(E_DOUBLE_NAME, line, c);

}
