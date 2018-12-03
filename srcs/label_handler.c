#include "asm.h"

// bool    label_exists(char *line)
// {
// 	size_t	counter;

// 	counter = -1;
// 	while ((ft_strchr(LABEL_CHARS, line[++counter])))
// 	{
// 		if (line[counter + 1] == LABEL_CHAR)
// 			return (true);
// 	}
// 	return (false);
// }

// bool	is_invalid_symbols(char *line, size_t label_len)
// {
// 	size_t	label_counter;

// 	label_counter = 0;
// 	while (label_counter < label_len)
// 	{
// 		if (!(ft_strchr(LABEL_CHARS, line[label_counter])))
// 			return (true);
// 		label_counter++;
// 	}
// 	return (false);
// }

// bool    is_label_without_instruction(char *line, t_counter *counter)
// {
// 	size_t	label_counter;

// 	label_counter = 0;
// 	char *new = ft_strtok(line, ":");
// 	if (is_valid_symbols(new, ft_strcspn(new, LABEL_CHARS))
// 	printf("new: %s\n", new);
// 	while (true)
// 	{
// 		if (line[label_counter] == '\0' || is_whitespaces(line[label_counter + 1]))
// 			return (false);
// 		if (line[label_counter] == LABEL_CHAR)
// 			break ;
// 		label_counter++;
// 	}
// 	if (is_invalid_symbols(line, label_counter))
// 	{
// 		counter->column = label_counter;
// 		semantic_errors(E_SEMANTIC_ERROR, line, counter);
// 	}
// 	counter->column += label_counter;
// 	return (true);
// }

// char    *new_label(char *line, t_counter *counter)
// {
// 	char	*label;

// 	label = NULL;
// 	while (line[counter->column])
// 	{
// 		if (line[counter->column] == LABEL_CHAR)
// 		{
// 			label = ft_strsub(line, 0, counter->column++);
// 			break ;
// 		}
// 		if (!(ft_strchr(LABEL_CHARS, line[counter->column])))
// 			semantic_errors(E_SEMANTIC_ERROR, line, counter);
// 		counter->column++;
// 	}
// 	return (label);
// }

void    append_label(t_list **label_head, char *label)
{
	ft_lstaddend(label_head, ft_lstnew(label, ft_strlen(label) + 1));
	// free(label);
}
