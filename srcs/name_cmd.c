#include "asm.h"

static char	*name_str_get(char *line, size_t name_len, t_counter *c)
{
	size_t	after_end_quotes;
	char	*name;

	name = NULL;
	after_end_quotes = c->column + name_len + 1;
	after_end_quotes += ft_strspn(line + after_end_quotes, DELIMS_CHARS);
	if (!line[after_end_quotes])
		name = ft_strsub(line, c->column, name_len);
	else
	{
		c->column = after_end_quotes + 1;
		lexical_errors(E_INVALID_SYMBOLS, line, c);
	}
	return (name);
}

static void	name_str_set(t_header *h, char *line, t_counter *c)
{
	size_t	name_len;
	char	*name;

	name_len = -1;
	name = NULL;
	while (++name_len < PROG_NAME_LENGTH)
	{
		if (line[c->column + name_len] == QUOTES_CHAR)
		{
			name = name_str_get(line, name_len, c);
			ft_strncpy(h->prog_name, name, name_len);
			ft_strdel(&name);
			return ;
		}
		if (!line[c->column + name_len + 1])
		{
			c->column += name_len + 2;
			lexical_errors(E_NO_END_QUOTES, line, c);
		}
	}
	lexical_errors(E_CHAMPION_NAME_TOO_LONG, line, c);
}

bool		is_name_cmd(char *str)
{
	return (ft_strnequ(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)));
}

void		name_get(t_header *h, char *line, t_counter *c)
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
