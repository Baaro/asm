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

static char		*file_del_comment(char *line)
{
	char	*comment_char;
	char	*new_line;

	if (!line)
		return (NULL);
	new_line = NULL;
	if ((comment_char = ft_strchr(line, COMMENT_CHAR)))
		new_line = ft_strsub(line, 0, comment_char - line);
	else if ((comment_char = ft_strchr(line, COMMENT_CHAR_ALTER)))
		new_line = ft_strsub(line, 0, comment_char - line);
	else
		return (line);
	free(line);
	return (new_line);
}

int			file_get_line(t_file *file, t_counter *counter)
{
	int		status;

	while ((status = get_next_line(file->fd, &file->line) == 1))
	{
		counter->row++;
		counter->whitespaces = get_whitespaces(file->line);
		if (is_endline_or_comment(file->line))
			continue ;
		file->line = file_del_comment(file->line);
		file->line = ft_strretrim(file->line);
		file->data = file_append_data(file->data, file->line);
		break ;
	}
	return (status);
}
