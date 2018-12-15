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

void				arguments_get_str(t_token *token, t_counter *c)
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

// static t_argument	argument_get(uint8_t instr_code, char *arg_str)
// {
// 	t_argument	arg;

// 	if (is_reg(arg_str))
// 		arg = reg_get(instr_code, arg_str);
// 	else if (is_dir(arg_str))
// 		arg = dir_get(instr_code, arg_str);
// 	else if (is_ind(arg_str))
// 		arg = dir_get(instr_code, arg_str);
// 	return (arg);
// }

// void				arguments_set(t_bytecode *b_token, t_token *token)
// {
// 	uint8_t		shift;
// 	ssize_t		curr_arg;
	
// 	shift = 6;
// 	curr_arg = -1;
// 	while (++curr_arg < MAX_ARGS_NUMBER - 1)
// 	{
// 		if (token->args[curr_arg])
// 		{
// 			b_token->args[curr_arg] = argument_get(b_token->instr_code, token->args[curr_arg]);
// 			b_token->args_code |= b_token->args[curr_arg].code << shift;
// 			shift -= 2;
// 		}
// 	}
// }
