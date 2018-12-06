// #include "asm.h"

// static bool	is_endline_or_comment(char *str)
// {
//     return (!(*str) || ft_strspn(str, "\n;#") > 0);
// }


// int			file_get_line(t_file *file, t_counter *counter)
// {
// 	int		status;

// 	while ((status = get_next_line(file->fd, &file->line) == 1))
// 	{
// 		counter->row++;
// 		counter->column = 0;
// 		counter->begin_whitespaces = ft_strspn(file->line, DELIMS_CHARS);
// 		if (is_endline_or_comment(file->line + counter->begin_whitespaces))
// 			continue ;
// 		file->line = ft_strcutuntil(file->line, COMMENT_CHARS);
// 		file->line = ft_strretrim(file->line);
// 		file->data = file_append_data(file->data, file->line);
// 		break ;
// 	}
// 	return (status);
// }
