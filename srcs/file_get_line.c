#include "asm.h"

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

int			file_get_line(t_file *file)
{
	int		status;

	status = get_next_line(file->fd, &file->line);
	file->data = file_append_data(file->data, file->line);
	return (status);
}
