#include "asm.h"

static void			argument_valid_str(char *arg, t_counter *c)
{
	ssize_t	invalid_symbol;

	if ((invalid_symbol = get_invalid_symbols(arg, ft_strlen(arg), VALID_CHARS)) != -1)
	{
		c->column += (size_t)invalid_symbol - 1;
		lexical_errors(E_INVALID_SYMBOLS, arg, c);
	}
}

void			arguments_get_str(t_token *token, t_counter *c)
{
	ssize_t	i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER - 1)
	{
		token->args[i] = ft_strtrim(ft_strtok(NULL, ","));
		if (token->args[i])
			argument_valid_str(token->args[i], c);
	}
}
