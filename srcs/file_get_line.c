#include "asm.h"

static bool	is_endline_or_comment(char *str)
{
	if (!(*str) || ft_strspn(str, "\n;#") > 0)
		return (true);
	return (false);
}

static char		*file_append_data(char *data, char *line)
{
	char 	*without_endline;
    char    *with_endline;

	without_endline = data == NULL ? ft_strnew(0) : data;
	without_endline = ft_strjoincl(without_endline, line, 0);
	with_endline = ft_strjoincl(without_endline, "\n", 0);
    data = with_endline;
	return (data);
}

int			file_get_line(t_file *file, t_counter *counter)
{
	int		status;

	while ((status = get_next_line(file->fd, &file->line) == 1))
	{
		counter->row++;
		counter->column = 0;
		counter->begin_whitespaces = ft_strspn(file->line, DELIMS_CHARS);
		if (is_endline_or_comment(file->line + counter->begin_whitespaces))
			continue ;
		file->line = ft_strcutuntil(file->line, COMMENT_CHARS);
		file->line = ft_strretrim(file->line);
		file->data = file_append_data(file->data, file->line);
		break ;
	}
	return (status);
}
