#include "asm.h"

static bool	is_endline_or_comment(char *c)
{
	if (*c == ENDLINE_CHAR || *c == ENDSTRING_CHAR)
		return (true);
	else if (*c == COMMENT_CHAR || *c == COMMENT_CHAR_ALTER)
		return (true);
	return (false);
}

static char		*file_append_data(char *data, char *line)
{
	char 	*endline_char;
	char 	*without_endline;
    char    *with_endline;

	without_endline = data == NULL ? ft_strnew(0) : data;
	endline_char = ft_strdup("\n");
	without_endline = ft_strjoincl(without_endline, line, 0);
	with_endline = ft_strjoincl(without_endline, endline_char, 1);
    data = with_endline;
	return (data);
}

int			file_get_line(t_file *file, t_counter *counter)
{
	int		status;

	while ((status = get_next_line(file->fd, &file->line) == 1))
	{
		counter->row++;
		counter->column = shift_whitespaces(file->line);
		// file->line = ft_strdupcl(file->line, file->line + counter->column);
		file->line = ft_memmove(file->line, file->line + counter->column, \
									 				ft_strlen(file->line));
		file->data = file_append_data(file->data, file->line);
		if (is_endline_or_comment(file->line))
			continue ;
		break ;
	}
	return (status);
}
