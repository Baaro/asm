#include "asm.h"

static char	*cmd_str_get(char *line, size_t str_len, t_counter *c)
{
	size_t	after_end_quotes;
	char	*str;

	str = NULL;
	after_end_quotes = c->column + str_len + 1;
	after_end_quotes += ft_strspn(line + after_end_quotes, DELIMS_CHARS);
	if (!line[after_end_quotes])
		str = ft_strsub(line, c->column, str_len);
	else
	{
		c->column = after_end_quotes + 1;
		lexical_errors(E_INVALID_SYMBOLS, line, c);
	}
	return (str);
}

static void	cmd_str_set(t_header *h, char *line, size_t maxstrlen, t_counter *c)
{
	size_t	str_len;
	char	*str;

	str_len = -1;
	str = NULL;
	while (++str_len < maxstrlen)
	{
		if (line[c->column + str_len] == QUOTES_CHAR)
		{
			str = cmd_str_get(line, str_len, c);
			if (h->cmd_choose)
				ft_strncpy(h->prog_name, str, str_len);
			else
				ft_strncpy(h->comment, str, str_len);
			ft_strdel(&str);
			return ;
		}
		if (!line[c->column + str_len + 1])
		{
			c->column += str_len + 2;
			lexical_errors(E_NO_END_QUOTES, line, c);
		}
	}
	if (h->cmd_choose)
		lexical_errors(E_CHAMPION_NAME_TOO_LONG, line, c);
	lexical_errors(E_CHAMPION_COMMENT_TOO_LONG, line, c);
}

static void		cmd_set(t_header *h, char *line, t_counter *c)
{
	size_t	max_str_len;

	if (h->cmd_choose)
	{
		max_str_len = PROG_NAME_LENGTH + 1;
		if (!h->prog_name[0])
			c->column = ft_strlen(NAME_CMD_STRING);
		else
			semantic_errors(E_DOUBLE_NAME, line, c);
	}
	else
	{
		max_str_len = COMMENT_LENGTH + 1;
		if (!h->comment[0])
			c->column = ft_strlen(COMMENT_CMD_STRING);
		else
			semantic_errors(E_DOUBLE_COMMENT, line, c);
	}
	if (line[c->column] == QUOTES_CHAR)
	{
		c->column++;
		command_str_set(h, line, max_str_len, c);
	}
	else
		lexical_errors(E_NO_BEGIN_QUOTES, line, c);
}

void			cmd_get(t_header *h, char *line, t_counter *c)
{
	if (ft_strnequ(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		h->cmd_choose = true;
	else if (ft_strnequ(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		h->cmd_choose = false;
	else
		semantic_errors(E_UNMATCHED_COMMAND, line, c);
	cmd_set(h, line, c);
}
