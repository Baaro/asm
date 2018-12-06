#include "asm.h"

static t_header	*header_new(void)
{
	return (ft_memalloc(sizeof(t_header)));
}

static bool		is_dot_char(char *c)
{
	return (*c == HEADER_DOT_CHAR);
}

static void		header_valid(t_header *h, char *data, t_counter *c)
{
	size_t	header_commands;
	size_t	status;
	char	*line;

	line = NULL;
	header_commands = 0;
	while ((status = file_get_line(data, &line, c)) == 1)
	{
		if (is_dot_char(line))
		{
			cmd_get(h, line, c);
			if (++header_commands == VALID)
				return (true);
		}
		else
			syntactic_errors(E_NOT_ALL_COMMAND, line, c);
	}
	if (status == 0)
		lexical_errors(E_IS_NOT_ENOUGH_DATA, line, c);
}

void			header_del(t_header **h)
{
	ft_memdel((void **)h);
}

t_header		*header_set(char *data, t_counter *c)
{
	t_header    *h;

	h = header_new();
	header_valid(h, data, c);
	return (h);
}
