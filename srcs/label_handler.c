#include "asm.h"

char			*get_label(char *line, t_counter *counter)
{
	size_t	label_char;
	ssize_t	invalid_symbol;

	label_char = ft_strcspn(line, ":");
	if (line[label_char] == LABEL_CHAR)
	{
		if ((invalid_symbol = get_invalid_symbols(line, label_char - 1)) == -1)
		{
			counter->column += label_char;
			return (ft_strsub(line, 0, label_char));
		}
	}
	return (NULL);
}

char			*get_solo_label(char *line, t_counter *counter)
{
	ssize_t	invalid_symbol;
	size_t	label_char;

	label_char = ft_strcspn(line, ":");
	if (line[label_char] == LABEL_CHAR
	&& line[label_char + 1] == '\0')
	{
		if ((invalid_symbol = get_invalid_symbols(line, label_char - 1)) != -1)
		{
			counter->column += (size_t)invalid_symbol;
			lexical_errors(E_INVALID_SYMBOLS, line, counter);
		}
		return (ft_strsub(line, 0, label_char));
	}
	return (NULL);
}

void    append_label(t_list **label_head, char *label)
{
	ft_lstaddend(label_head, ft_lstnew(label, ft_strlen(label) + 1));
	// ft_strdel(label);
}
