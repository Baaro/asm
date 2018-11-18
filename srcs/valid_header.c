#include "info.h"

bool     ft_get_line(char *data, char **line) // test version
{
    static char *tail;
    char        *pos;

    if (!line)
        return (false);
    else if (*line)
        free(*line);
    tail = tail == NULL ? (char *)data : ft_strjoincl(tail, data, 0);
    while (tail)
    {
        if ((pos = ft_strchr(tail, '\n')))
        {
            *line = ft_strsub(tail, 0, tail - pos);
            tail = ft_strredup(tail, pos + 1);
            return (true);
        }
    }
    return (false);
}

// bool	is_label(const char *line)
// {

// }

// bool	is_instruction(const char *line)
// {

// }

void	valid_header(char *data, unsigned int *row, unsigned int *column) // test version
{
	char	*line;
    bool    checker;

	line = NULL;
    *column = 0;
	while ((checker = ft_get_line(data, &line)) == 1)
	{
		(*row)++;
		// if (is_label(line) || is_instruction(line))
			// break ;
		// valid_line(line, column);
	}
    // if (checker == 0 && (*row) == 0)
    //     errors(FILE_IS_EMPTY);
}
