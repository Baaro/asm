#include "asm.h"

size_t		get_currunet_column(t_counter *counter)
{
	return (counter->column + counter->begin_whitespaces); 
}

size_t		get_currunet_position(t_counter *counter)
{
	return (counter->column);
}

bool	is_whitespaces(const char c)
{
	return (c == '\t' || c == ' ');
}

void			ft_lstprint(t_list *elem)
{
	if (elem)
	{
		printf("%s\n", ((t_label *)elem->content)->name);
	}
}

bool				is_valid_val(char *arg_str)
{
	if (*arg_str == '-')
		arg_str++;
	while (ft_isdigit(*arg_str))
	{
		if (*(arg_str + 1) == '\0')	
			return (true);
		arg_str++;
	}
	return (false);
}

void			token_print(t_list *token)
{
	ssize_t i;

	printf("\n-----------TOKEN-----------\n");
	printf("LABELS:\n");
	ft_lstiter(((t_token *)token->content)->labels, ft_lstprint);
	printf("INSTRUCTION: [%s]\n", ((t_token *)token->content)->instr);
	printf("ARGUMENTS:\n");
	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
		printf("arg[%zu] -> %s\n", i, (*(t_token*)token->content).args[i]);
	printf("\n-----------TOKEN-----------\n");
}

ssize_t			get_invalid_symbols(char *line, size_t len, char *valid_symbols)
{
	ssize_t	i;

	i = -1;
	while (line[++i] && i < (ssize_t)len)
	{
		if (!ft_strchr(valid_symbols, line[i]))
			return(i);
	}
	return (i == len ? -1 : i);
}


