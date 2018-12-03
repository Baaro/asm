#include "asm.h"

static char	*get_name(char *line, size_t name_len, t_counter *counter)
{
	size_t	after_end_quotes;
	char	*name;

	name = NULL;
	after_end_quotes = counter->column + name_len + 1;
	after_end_quotes += ft_strspn(line + after_end_quotes, DELIMS_CHARS);
	if (!line[after_end_quotes])
		name = ft_strsub(line, counter->column, name_len);
	else
	{
		counter->column = after_end_quotes + 1;
		lexical_errors(E_INVALID_SYMBOLS, line, counter);
	}
	return (name);
}

static void	set_name(t_file *file, t_counter *counter)
{
	size_t	name_len;
	char	*name;

	name_len = -1;
	name = NULL;
	while (++name_len < PROG_NAME_LENGTH)
	{
		if (file->line[counter->column + name_len] == QUOTES_CHAR)
		{
			name = get_name(file->line, name_len, counter);
			ft_strncpy(file->hdr.prog_name, name, name_len);
			ft_strdel(&name);
			return ;
		}
		if (!file->line[counter->column + name_len + 1])
		{
			counter->column += name_len + 2;
			lexical_errors(E_NO_END_QUOTES, file->line, counter);
		}
	}
	lexical_errors(E_CHAMPION_NAME_TOO_LONG, file->line, counter);
}

bool		is_name_cmd(char *str)
{
	return (ft_strnequ(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)));
}

void		valid_name(t_file *file, t_counter *counter)
{
	if (!file->hdr.prog_name[0])
	{
		counter->column = ft_strlen(NAME_CMD_STRING);
		counter->column += ft_strspn(file->line + counter->column, DELIMS_CHARS);
		if (file->line[counter->column] == QUOTES_CHAR)
		{
			counter->column++;
			set_name(file, counter);
		}
		else
			lexical_errors(E_NO_BEGIN_QUOTES, file->line, counter);
	}
	else
		semantic_errors(E_DOUBLE_NAME, file->line, counter);
}
