#include "asm.h"

static bool is_endline(char *str)
{
    return (*str == '\n');
}

static bool	is_comment(char *str)
{
	return (*str == ';' || *str == '#');
}

char		*file_append_data(char **data, char **line, bool ret_with_endline)
{
	char 	*without_endline;
	char    *with_endline;

	without_endline = *data == NULL ? ft_strnew(0) : *data;
	without_endline = ft_strjoincl(without_endline, *line, 0);
	if (ret_with_endline)
		*line = ft_strjoincl(*line, "\n", 0);
	with_endline = ft_strjoincl(without_endline, "\n", 0);
	*data = with_endline;
	return (*data);
}

int         file_get_line(t_file *f, t_counter *c, bool is_header)
{
	int		status;

	while ((status = get_next_line(f->fd, &f->line) == 1))
	{
		c->row++;
		c->column = 0;
		if (!is_header)
		{
			c->begin_whitespaces = ft_strspn(f->line, DELIMS_CHARS);
			if (is_endline(f->line + c->begin_whitespaces)
			|| is_comment(f->line + c->begin_whitespaces))
				continue ;
			f->line = ft_strcutuntil(f->line, COMMENT_CHARS);
			f->line = ft_strretrim(f->line);
		}
		f->data = file_append_data(&f->data, &f->line, is_header);
		break ;
	}
	return (status);
}
